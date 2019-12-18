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
typedef  double double_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 int /*<<< orphan*/  SET_LOW_WORD (double,int /*<<< orphan*/ ) ; 
 double* T ; 
 double pio4 ; 
 double pio4lo ; 

double __tan(double x, double y, int odd)
{
	double_t z, r, v, w, s, a;
	double w0, a0;
	uint32_t hx;
	int big, sign;

	GET_HIGH_WORD(hx,x);
	big = (hx&0x7fffffff) >= 0x3FE59428; /* |x| >= 0.6744 */
	if (big) {
		sign = hx>>31;
		if (sign) {
			x = -x;
			y = -y;
		}
		x = (pio4 - x) + (pio4lo - y);
		y = 0.0;
	}
	z = x * x;
	w = z * z;
	/*
	 * Break x^5*(T[1]+x^2*T[2]+...) into
	 * x^5(T[1]+x^4*T[3]+...+x^20*T[11]) +
	 * x^5(x^2*(T[2]+x^4*T[4]+...+x^22*[T12]))
	 */
	r = T[1] + w*(T[3] + w*(T[5] + w*(T[7] + w*(T[9] + w*T[11]))));
	v = z*(T[2] + w*(T[4] + w*(T[6] + w*(T[8] + w*(T[10] + w*T[12])))));
	s = z * x;
	r = y + z*(s*(r + v) + y) + s*T[0];
	w = x + r;
	if (big) {
		s = 1 - 2*odd;
		v = s - 2.0 * (x + (r - w*w/(w + s)));
		return sign ? -v : v;
	}
	if (!odd)
		return w;
	/* -1.0/(x+r) has up to 2ulp error, so compute it accurately */
	w0 = w;
	SET_LOW_WORD(w0, 0);
	v = r - (w0 - x);       /* w0+v = r+x */
	a0 = a = -1.0 / w;
	SET_LOW_WORD(a0, 0);
	return a0 + a*(1.0 + a0*w0 + a0*v);
}