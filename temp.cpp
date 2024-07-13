------------------------------------------Most Frequent Value----------------------------------
#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
//#define int long long
const int N = 1e5+5 ,M=1e6+5,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e9+7;
bool comp(pair<int, int> &a,pair<int,int> &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}
struct Query {
    int l, r, iq;
};
int n ,ans , vis[1000005] , fre[M] , fre_fre[N];
vector<int>a;
void add(int x) {
    fre_fre[fre[x]]--;
    fre[x]++;
    ans=max(ans,fre[x]);
    fre_fre[fre[x]]++;
}
void remove(int x) {
    fre_fre[fre[x]]--;
    if (fre_fre[ans] == 0)
        --ans;
    fre[x]--;
    fre_fre[fre[x]]++;

}
vector<int> MO_process(vector<Query>&qu) {
    const int SQ = ceil(sqrt(n)) + 1;
    sort(qu.begin(), qu.end(),
         [&](const Query &x, const Query &y) -> bool {
             if (x.l / SQ == y.l / SQ)
                 return x.r < y.r;
             return x.l / SQ < y.l / SQ;
         }
    );
    int l = qu[0].l, r = qu[0].l;
    add(a[qu[0].l]);
    vector<int> res(qu.size());
    for (const auto &[lq, rq, iq]: qu) {
        while (r < rq)add(a[++r]);
        while (l < lq)remove(a[l++]);
        while (l > lq)add(a[--l]);
        while (r > rq)remove(a[r--]);
        res[iq] = ans;
    }
    return res;
}
void solve() {
    int q;
    cin>>n >> q;
    a.assign(n, {});

    map<int, int> mp;
    for (int &i: a)cin >> i , mp[i]++;
    int id = 0;
    for (auto &[u, v]: mp)v = id++;
    for (int &i: a)i = mp[i];

    vector<Query> Q(q);
    for (int i = 0; i < q; ++i) {
        cin >> Q[i].l >> Q[i].r;
//        --Q[i].l , --Q[i].r;
        Q[i].iq = i;
    }
    auto res = MO_process(Q);
    for (int &it: res)cout << it << "\n";
}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
---------------------------------------------------------------MIX------------------------------------------------------------------
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,M=1e6+5,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e9+7 , SQ=317;
bool comp(pair<int, int> &a,pair<int,int> &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}
struct Query {
    int l, r, iq;
};
int n , fre[N] , B[SQ] ; // B : each block contain any num of distinct elements ?
vector<int>a;
void add(int x) {
    fre[x]++;
    if (fre[x] == 1) {
        B[x / SQ] += 1;
    }
}
void remove(int x) {
    fre[x]--;
    if (!fre[x]) {
        B[x / SQ]--;
    }
}
int ans() {
    int i = 0;
    while (B[i] == SQ)i++;
    i *= SQ;
    while (fre[i])i++;
    return i;
}
vector<int> MO_process(vector<Query>&qu) {
//    const int SQ = ceil(sqrt(n)) + 1;
    sort(qu.begin(), qu.end(),
         [&](const Query &x, const Query &y) -> bool {
             if (x.l / SQ == y.l / SQ)
                 return x.r < y.r;
             return x.l / SQ < y.l / SQ;
         }
    );
    int l = qu[0].l, r = qu[0].l;
    add(a[qu[0].l]);
    vector<int> res(qu.size());
    for (const auto &[lq, rq, iq]: qu) {
        while (r < rq)add(a[++r]);
        while (l < lq)remove(a[l++]);
        while (l > lq)add(a[--l]);
        while (r > rq)remove(a[r--]);
        res[iq] = ans();
    }
    return res;
}
void solve() {
    int q;
    cin >> n >> q;
    a.assign(n, {});
    for (int &i: a)cin >> i;
    vector<Query> Q(q);
    for (int i = 0; i < q; ++i) {
        cin >> Q[i].l >> Q[i].r;
//        --Q[i].l , --Q[i].r;
        Q[i].iq = i;
    }
    auto res = MO_process(Q);
    for (int &it: res)cout << it << "\n";
}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
----------------------------------------------------------------num of distinct element----------------------------------------------------------
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 3e4+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e9+7;
bool comp(pair<int, int> &a,pair<int,int> &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}
struct Query {
    int l, r, iq;
};
int n ,ans=0 , vis[1000005] ;
vector<int>a;
void add(int x) {
    if (!vis[x]) {
        ans++;
    }
    vis[x]++;
}
void remove(int x) {
    vis[x]--;
    if (!vis[x]) {
        ans--;
    }
}
vector<int> MO_process(vector<Query>&qu) {
    const int SQ=ceil(sqrt(n))+1 ;
    sort(qu.begin(), qu.end(),
         [&](const Query &x , const Query &y) -> bool {
             if(x.l/SQ == y.l/SQ)
                 return x.r<y.r;
             return x.l/SQ < y.l/SQ;
        }
    );
    int l = qu[0].l, r = qu[0].l;
    add(a[qu[0].l]);
    vector<int>res(qu.size());
    for(const auto & [lq,rq,iq] : qu){
        while (l < lq)remove(a[l++]);
        while (l > lq)add(a[--l]);
        while (r < rq)add(a[++r]);
        while (r > rq)remove(a[r--]);
        res[iq] = ans;
    }
    return res;
}
void solve() {
    cin >> n;
    a.assign(n,{});
    for(auto &i : a)cin >> i ;
    int q ;
    cin >> q;
    vector<Query>Q(q);
    for (int i = 0; i < q; ++i) {
        cin >> Q[i].l >> Q[i].r ;
        --Q[i].l , --Q[i].r;
        Q[i].iq=i;
    }
    auto res = MO_process(Q);
    for(auto it : res)cout<<it<<"\n";
}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
++++++++++++++++++++++++
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 3e4+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e9+7;
bool comp(pair<int, int> &a,pair<int,int> &b) {
    if (a.first != b.first) return a.first > b.first;
    return a.second < b.second;
}
const int SQ= sqrt(N) , num_of_queries=2e5+5;
struct query{
    int l , r , blk_idx , q_idx ;
    query(){}
    query(int _l , int _r ,int _q_idx){
        l=_l , r=_r , q_idx=_q_idx , blk_idx=_l/SQ;
    }
    // sort queries
    bool operator<(const query &q)const{
        if(blk_idx!=q.blk_idx){
            return blk_idx<q.blk_idx;
        }
        return r<q.r;
    }
};
int n , q ,res=0 , vis[1000005] , L=0 ,R=0 , a[N],first=1,ans[num_of_queries];
query qu[num_of_queries];
void add(int idx){
    if(!vis[a[idx]]){
        res++;
    }
    vis[a[idx]]++;
}
void remove(int idx){
    vis[a[idx]]--;
    if(!vis[a[idx]]){
        res--;
    }
}
void MO_process(){
    sort(qu,qu+q);
    int l=1 , r=0 ;
    for (int i = 0; i < q; ++i) {
        while (l<qu[i].l)remove(l++);
        while (l>qu[i].l)add(--l);
        while (r<qu[i].r)add(++r);
        while (r>qu[i].r)remove(r--);
        ans[qu[i].q_idx]=res;
    }
}
void solve() {
    cin >> n ;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> q ;
    for (int i = 0; i < q; ++i) {
        int l , r ;
        cin >> l >> r ;
        l--, r--;
        // i:query index
        qu[i]=query(l,r,i);
    }
    MO_process();
    for (int i = 0; i < q; ++i) {
        cout<<ans[i]<<"\n";
    }
}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
--------------------------------------------------------num of elements >= x in range with update--------------------------------------
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 5e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
const int SQ= 317 , num_of_queries=1e5+5;
vector<int>block[SQ];
vector<int>v;
//int ign = 1e9+5 ;
bool mrg(int a , int b) {
    return a >= b;
}
void build() {
    for (int i = 0; i < v.size(); ++i) {
        block[i/SQ].emplace_back(v[i]);
    }
    for (auto &i: block)sort(i.begin(), i.end());
}
void update(int i , int val) {
    int l = i - i % SQ, r = l + SQ - 1, res = 0;
    v[i] = val;
    block[i / SQ] = vector<int>(v.begin() + l, v.begin() + r + 1);;
    sort(block[i / SQ].begin(), block[i / SQ].end());
}
int query(int l , int r , int c) {
    int res = 0;
    while (l <= r && l % SQ) {
        res += (mrg(v[l], c)) ? 1 : 0;
        l++;
    }
    while (l + SQ - 1 <= r) {
        res += block[l / SQ].end() - lower_bound(block[l / SQ].begin(), block[l / SQ].end(), c);
        l += SQ;
    }
    while (l <= r) {
        res += (mrg(v[l], c)) ? 1 : 0;
        l++;
    }
    return res;
}
void solve() {
    int n, q;
    cin >> n;
    v = vector<int>(n);
    for (auto &i: v)cin >> i;
    build();
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            update(--pos, val);
        } else {
            int l, r , c;
            cin >> l >> r >> c;
            cout << query(--l, --r,c) << "\n";
        }
    }
}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
((((((((((((((((((segment tree)))))))))))))))))))))))))
---------------------------------------------------Minimum in range with update---------------------------------
#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz ;
struct SegTree {
    vector<int> seg;
    int temp=1e9+1;
    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n),temp);
    }
    int mrg(int a , int b){
        return min(a,b);
    }
    void update(int idx, int val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = val;
            return;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);

        seg[p] = mrg(seg[2 * p], seg[2 * p + 1]);
    }
    int get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r)return seg[p];       // totally inside
        if (st > r || end < l) return temp; // totally outside
        int mid = (st + end) / 2;
        int L = get(l, r, st, mid, 2 * p);
        int R = get(l, r, mid + 1, end, 2 * p + 1);
        return mrg(L, R);
    }
};
void solve() {
    int n , q ;
    cin >> n >> q ;
    SegTree se(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        se.update(i,x);
    }
    while (q--){
        int type ;
        cin >> type ;
        if(type==1){
            int pos , val ;
            cin >> pos >> val ;
            se.update(pos+1,val);
        }
        else {
            int l , r ;
            cin >> l >> r ;
            cout<<se.get(l+1,r)<<"\n";
        }
    }

}

int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
----------------------------------------------Number of Minimums on a Segment------------------------------------
#include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz;
struct SegTree {
    struct node{
        int mn ,  cnt ;
        node(){}
        node(int val , int c){
            mn=val;
            cnt=c;
        }
    };
    vector<node> seg;
    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n),{LLONG_MAX,0});
    }
    int mrg(int a , int b){
        return min(a,b);
    }
    node merge_nodes(node l ,node r) {
        node ans;
        if (l.mn == r.mn) {
            ans.mn = l.mn;
            ans.cnt = l.cnt + r.cnt;
            return ans;
        }
        if (l.mn < r.mn) {
            ans.mn = l.mn;
            ans.cnt = l.cnt;
            return ans;
        }
        if (l.mn > r.mn) {
            ans.mn = r.mn;
            ans.cnt = r.cnt;
            return ans;
        }
    }
    void update(int idx, int val ,int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p].mn=val;
            seg[p].cnt=1;
            return ;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);
        node l = seg[2*p] , r= seg[2*p+1];
        if (l.mn == r.mn) {
            seg[p].mn = l.mn;
            seg[p].cnt = l.cnt + r.cnt;
        }
        if (l.mn < r.mn) {
            seg[p].mn = l.mn;
            seg[p].cnt = l.cnt ;
        }
        if (l.mn > r.mn) {
            seg[p].mn = r.mn;
            seg[p].cnt = r.cnt;
        }
    }
    node get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r){
            return seg[p];// totally inside
        }
        if (st > r || end < l)  return node(LLONG_MAX,1);; // totally outside
        int mid = (st + end) / 2;
        node L = get(l, r, st, mid, 2 * p);
        node R = get(l, r, mid + 1, end, 2 * p + 1);
        if (L.mn == R.mn) {
            return node(L.mn,L.cnt + R.cnt);
        }
        if (L.mn < R.mn) {
            return node(L.mn,L.cnt);
        }
        if (L.mn > R.mn) {
            return node(R.mn,R.cnt);
        }
    }
};
void solve() {
    int n , q ;
    cin >> n >> q ;
    SegTree seg(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        seg.update(i,x);
    }
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, val;
            cin >> pos >> val;
            seg.update(pos+1, val);
        } else {
            int l, r;
            cin >> l >> r;
            cout<<seg.get(l+1,r).mn<<" "<<seg.get(l+1,r).cnt<<"\n";
        }
    }

}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
---------------------------------------maximumSubArray in range--------------------------
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz;
struct node {
    int sum, mx, pre, suff;
};
struct SegTree {

    int mn = -1e16 + 5;
    node temp = {mn, mn, mn, mn};
    vector<node> seg;

    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n), temp);
    }

    node merge_nodes(node l, node r) {
        node ans = temp;
        ans.sum = l.sum + r.sum;
        ans.pre = max(l.pre, l.sum + r.pre);
        ans.suff = max(r.suff, l.suff + r.sum);
        ans.mx = max({l.mx, r.mx, l.suff + r.pre, l.sum + r.sum});
        return ans;
    }

    void update(int idx, node val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = val;
            return;
        }
        int mid = (st + end) >> 1;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);
        node l = seg[2 * p], r = seg[2 * p + 1];
        seg[p] = merge_nodes(l, r);
    }

    node get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r)return seg[p];           // totally inside
        if (st > r || end < l) return temp;             // totally outside
        int mid = (st + end) >> 1;
        node L = get(l, r, st, mid, 2 * p);
        node R = get(l, r, mid + 1, end, 2 * p + 1);
        return merge_nodes(L, R);
    }
};
void solve() {
    int n , q ;
    cin >> n ;
    SegTree seg(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        seg.update(i,{x,x,x,x});
    }
    cin >> q ;
    while (q--) {
        int pos, val;
        cin >> pos >> val;
        cout<<seg.get(pos,val).mx<<"\n";
    }

}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
--------------------------------------minimum value in range with update-----------------------------------
  #include <bits/stdc++.h>
using namespace std;
#define FAST_DOT_COM  ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define int long long
const int N = 2e5+5 ,MOD=1e9+7, INF=0X3F3F3F3F , MAX= 1e12+5;
int sz ;
struct SegTree {
    vector<int> seg;
    int temp=LLONG_MAX;
    SegTree(int n) {
        sz = n;
        seg.assign(4 << __lg(n),temp);
    }
    int mrg(int a , int b){
        return min(a,b);
    }
    void update(int idx, int val, int st = 1, int end = sz, int p = 1) {
        if (st == end) {
            seg[p] = val;
            return;
        }
        int mid = (st + end) / 2;
        if (idx <= mid) update(idx, val, st, mid, p * 2);
        else update(idx, val, mid + 1, end, p * 2 + 1);

        seg[p] = mrg(seg[2 * p], seg[2 * p + 1]);
    }
    int get(int l, int r, int st = 1, int end = sz, int p = 1) {
        if (st >= l && end <= r)return seg[p];       // totally inside
        if (st > r || end < l) return temp; // totally outside
        int mid = (st + end) / 2;
        int L = get(l, r, st, mid, 2 * p);
        int R = get(l, r, mid + 1, end, 2 * p + 1);
        return mrg(L, R);
    }
};
void solve() {
    int n , q ;
    cin >> n >> q ;
    SegTree se(n);
    for (int i = 1; i <= n; ++i) {
        int x ;
        cin >> x ;
        se.update(i,x);
    }
    while (q--){
        int type ;
        cin >> type ;
        if(type==1){
            int pos , val ;
            cin >> pos >> val ;
            se.update(pos,val);
        }
        else {
            int l , r ;
            cin >> l >> r ;
            cout<<se.get(l,r)<<"\n";
        }
    }

}
int32_t main(){
    FAST_DOT_COM
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//#endif
    int t=1 ;
//    cin>>t ;
    while (t--) solve();
    return 0;
}
-------------------------------------------------------------------------------------------------------------
