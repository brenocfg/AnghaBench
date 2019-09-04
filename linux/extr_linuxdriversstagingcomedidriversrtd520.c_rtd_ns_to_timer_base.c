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

/* Variables and functions */
#define  CMDF_ROUND_DOWN 130 
 unsigned int CMDF_ROUND_MASK ; 
#define  CMDF_ROUND_NEAREST 129 
#define  CMDF_ROUND_UP 128 
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int DIV_ROUND_UP (unsigned int,int) ; 

__attribute__((used)) static int rtd_ns_to_timer_base(unsigned int *nanosec,
				unsigned int flags, int base)
{
	int divider;

	switch (flags & CMDF_ROUND_MASK) {
	case CMDF_ROUND_NEAREST:
	default:
		divider = DIV_ROUND_CLOSEST(*nanosec, base);
		break;
	case CMDF_ROUND_DOWN:
		divider = (*nanosec) / base;
		break;
	case CMDF_ROUND_UP:
		divider = DIV_ROUND_UP(*nanosec, base);
		break;
	}
	if (divider < 2)
		divider = 2;	/* min is divide by 2 */

	/*
	 * Note: we don't check for max, because different timers
	 * have different ranges
	 */

	*nanosec = base * divider;
	return divider - 1;	/* countdown is divisor+1 */
}