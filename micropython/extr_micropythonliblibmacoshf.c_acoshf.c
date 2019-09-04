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

/* Variables and functions */
 float log1pf (float) ; 
 float logf (float) ; 
 float sqrtf (float) ; 

float acoshf(float x)
{
	union {float f; uint32_t i;} u = {x};
	uint32_t a = u.i & 0x7fffffff;

	if (a < 0x3f800000+(1<<23))
		/* |x| < 2, invalid if x < 1 or nan */
		/* up to 2ulp error in [1,1.125] */
		return log1pf(x-1 + sqrtf((x-1)*(x-1)+2*(x-1)));
	if (a < 0x3f800000+(12<<23))
		/* |x| < 0x1p12 */
		return logf(2*x - 1/(x+sqrtf(x*x-1)));
	/* x >= 0x1p12 */
	return logf(x) + 0.693147180559945309417232121458176568f;
}