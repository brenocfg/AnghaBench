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
struct tc_ratespec {int mpu; int cell_log; int rate; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  TC_LINKLAYER_ATM ; 
 int /*<<< orphan*/  TC_LINKLAYER_ETHERNET ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int roundup (int,int) ; 

__attribute__((used)) static __u8 __detect_linklayer(struct tc_ratespec *r, __u32 *rtab)
{
	int low       = roundup(r->mpu, 48);
	int high      = roundup(low+1, 48);
	int cell_low  = low >> r->cell_log;
	int cell_high = (high >> r->cell_log) - 1;

	/* rtab is too inaccurate at rates > 100Mbit/s */
	if ((r->rate > (100000000/8)) || (rtab[0] == 0)) {
		pr_debug("TC linklayer: Giving up ATM detection\n");
		return TC_LINKLAYER_ETHERNET;
	}

	if ((cell_high > cell_low) && (cell_high < 256)
	    && (rtab[cell_low] == rtab[cell_high])) {
		pr_debug("TC linklayer: Detected ATM, low(%d)=high(%d)=%u\n",
			 cell_low, cell_high, rtab[cell_high]);
		return TC_LINKLAYER_ATM;
	}
	return TC_LINKLAYER_ETHERNET;
}