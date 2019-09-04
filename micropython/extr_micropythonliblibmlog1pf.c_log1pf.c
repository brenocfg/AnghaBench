#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  float float_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (float) ; 
 float Lg1 ; 
 float Lg2 ; 
 float Lg3 ; 
 float Lg4 ; 
 float ln2_hi ; 
 float ln2_lo ; 

float log1pf(float x)
{
	union {float f; uint32_t i;} u = {x};
	float_t hfsq,f,c,s,z,R,w,t1,t2,dk;
	uint32_t ix,iu;
	int k;

	ix = u.i;
	k = 1;
	if (ix < 0x3ed413d0 || ix>>31) {  /* 1+x < sqrt(2)+  */
		if (ix >= 0xbf800000) {  /* x <= -1.0 */
			if (x == -1)
				return x/0.0f; /* log1p(-1)=+inf */
			return (x-x)/0.0f;     /* log1p(x<-1)=NaN */
		}
		if (ix<<1 < 0x33800000<<1) {   /* |x| < 2**-24 */
			/* underflow if subnormal */
			if ((ix&0x7f800000) == 0)
				FORCE_EVAL(x*x);
			return x;
		}
		if (ix <= 0xbe95f619) { /* sqrt(2)/2- <= 1+x < sqrt(2)+ */
			k = 0;
			c = 0;
			f = x;
		}
	} else if (ix >= 0x7f800000)
		return x;
	if (k) {
		u.f = 1 + x;
		iu = u.i;
		iu += 0x3f800000 - 0x3f3504f3;
		k = (int)(iu>>23) - 0x7f;
		/* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
		if (k < 25) {
			c = k >= 2 ? 1-(u.f-x) : x-(u.f-1);
			c /= u.f;
		} else
			c = 0;
		/* reduce u into [sqrt(2)/2, sqrt(2)] */
		iu = (iu&0x007fffff) + 0x3f3504f3;
		u.i = iu;
		f = u.f - 1;
	}
	s = f/(2.0f + f);
	z = s*s;
	w = z*z;
	t1= w*(Lg2+w*Lg4);
	t2= z*(Lg1+w*Lg3);
	R = t2 + t1;
	hfsq = 0.5f*f*f;
	dk = k;
	return s*(hfsq+R) + (dk*ln2_lo+c) - hfsq + f + dk*ln2_hi;
}