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
typedef  unsigned long u64 ;
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 unsigned long __ffs (unsigned long) ; 
 long abs (unsigned long) ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int fls_long (unsigned long) ; 

__attribute__((used)) static unsigned int quark_x1000_get_clk_div(int rate, u32 *dds)
{
	unsigned long xtal = 200000000;
	unsigned long fref = xtal / 2;		/* mandatory division by 2,
						   see (2) */
						/* case 3 */
	unsigned long fref1 = fref / 2;		/* case 1 */
	unsigned long fref2 = fref * 2 / 5;	/* case 2 */
	unsigned long scale;
	unsigned long q, q1, q2;
	long r, r1, r2;
	u32 mul;

	/* Case 1 */

	/* Set initial value for DDS_CLK_RATE */
	mul = (1 << 24) >> 1;

	/* Calculate initial quot */
	q1 = DIV_ROUND_UP(fref1, rate);

	/* Scale q1 if it's too big */
	if (q1 > 256) {
		/* Scale q1 to range [1, 512] */
		scale = fls_long(q1 - 1);
		if (scale > 9) {
			q1 >>= scale - 9;
			mul >>= scale - 9;
		}

		/* Round the result if we have a remainder */
		q1 += q1 & 1;
	}

	/* Decrease DDS_CLK_RATE as much as we can without loss in precision */
	scale = __ffs(q1);
	q1 >>= scale;
	mul >>= scale;

	/* Get the remainder */
	r1 = abs(fref1 / (1 << (24 - fls_long(mul))) / q1 - rate);

	/* Case 2 */

	q2 = DIV_ROUND_UP(fref2, rate);
	r2 = abs(fref2 / q2 - rate);

	/*
	 * Choose the best between two: less remainder we have the better. We
	 * can't go case 2 if q2 is greater than 256 since SCR register can
	 * hold only values 0 .. 255.
	 */
	if (r2 >= r1 || q2 > 256) {
		/* case 1 is better */
		r = r1;
		q = q1;
	} else {
		/* case 2 is better */
		r = r2;
		q = q2;
		mul = (1 << 24) * 2 / 5;
	}

	/* Check case 3 only if the divisor is big enough */
	if (fref / rate >= 80) {
		u64 fssp;
		u32 m;

		/* Calculate initial quot */
		q1 = DIV_ROUND_UP(fref, rate);
		m = (1 << 24) / q1;

		/* Get the remainder */
		fssp = (u64)fref * m;
		do_div(fssp, 1 << 24);
		r1 = abs(fssp - rate);

		/* Choose this one if it suits better */
		if (r1 < r) {
			/* case 3 is better */
			q = 1;
			mul = m;
		}
	}

	*dds = mul;
	return q - 1;
}