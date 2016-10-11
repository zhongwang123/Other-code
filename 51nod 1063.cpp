#include <cmath>
#include <cstdio>
using namespace std;

typedef unsigned long long int LL;

typedef struct Record {
	LL a, b;
} Record;
Record f[64];
LL n;

void calc()
{
	int i;
	
	f[1].a = 1;
	f[1].b = 0;
	f[2].a = 0;
	f[2].b = 1;
	for (i = 3; i <= 63; ++i) {
		f[i].a = f[i - 1].a + f[i - 2].a;
		f[i].b = f[i - 1].b + f[i - 2].b;
	}
}

LL mymax(LL x, LL y)
{
	return x > y ? x : y;
}

LL bisearch(LL ll, LL rr, int cc, LL lv, LL rv)
{
	//++rd;
	//printf("rd = %d\n", rd);
	//printf("ll = %lld, rr = %lld, cc = %d, lv = %lld, rv = %lld\n", ll, rr, cc, lv, rv);

	LL mm, mv;
	LL ans;
	
	mm = ll + (rr - ll) / 2;
	mv = lv + rv;
	if (mm <= n + 1) {
		if (cc == 1) {
			ans = lv;
		} else if (lv < mv) {
			ans = lv * f[cc + 1].a + mv * f[cc + 1].b;
		} else {
			ans = mv * f[cc + 1].a + lv * f[cc + 1].b;
		}
		if (ll < mm && n >= mm) {
			//printf("BUG\n");
			ans = mymax(ans, bisearch(mm, rr, cc - 1, mv, rv));
		}
	} else {
		ans = bisearch(ll, mm, cc - 1, lv, mv);
	}
	return ans;
}

LL solve()
{
	LL ll, rr;
	int cc;
	
	ll = 1;
	cc = 0;
	while (ll * 2 <= n) {
		ll *= 2;
		++cc;
	}
	rr = ll * 2;
	LL ans = f[cc + 1].a + f[cc + 1].b;
	ans = mymax(ans, bisearch(ll, rr, cc, 1, 1));
	return ans;
}

int main()
{
	calc();

	int t, ti;
	scanf("%d", &t);
	for (ti = 0; ti < t; ++ti) {
		scanf("%llu", &n);
		printf("%llu\n", (LL)solve());
	}
	
	return 0;
}