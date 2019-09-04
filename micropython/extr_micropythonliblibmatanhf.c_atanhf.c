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
typedef  int float_t ;

/* Variables and functions */
 int /*<<< orphan*/  FORCE_EVAL (float) ; 
 float log1pf (int) ; 

float atanhf(float x)
{
	union {float f; uint32_t i;} u = {.f = x};
	unsigned s = u.i >> 31;
	float_t y;

	/* |x| */
	u.i &= 0x7fffffff;
	y = u.f;

	if (u.i < 0x3f800000 - (1<<23)) {
		if (u.i < 0x3f800000 - (32<<23)) {
			/* handle underflow */
			if (u.i < (1<<23))
				FORCE_EVAL((float)(y*y));
		} else {
			/* |x| < 0.5, up to 1.7ulp error */
			y = 0.5f*log1pf(2*y + 2*y*y/(1-y));
		}
	} else {
		/* avoid overflow */
		y = 0.5f*log1pf(2*(y/(1-y)));
	}
	return s ? -y : y;
}