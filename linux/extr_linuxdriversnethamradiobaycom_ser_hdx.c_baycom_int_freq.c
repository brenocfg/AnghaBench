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
struct baycom_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void baycom_int_freq(struct baycom_state *bc)
{
#ifdef BAYCOM_DEBUG
	unsigned long cur_jiffies = jiffies;
	/*
	 * measure the interrupt frequency
	 */
	bc->debug_vals.cur_intcnt++;
	if (time_after_eq(cur_jiffies, bc->debug_vals.last_jiffies + HZ)) {
		bc->debug_vals.last_jiffies = cur_jiffies;
		bc->debug_vals.last_intcnt = bc->debug_vals.cur_intcnt;
		bc->debug_vals.cur_intcnt = 0;
		bc->debug_vals.last_pllcorr = bc->debug_vals.cur_pllcorr;
		bc->debug_vals.cur_pllcorr = 0;
	}
#endif /* BAYCOM_DEBUG */
}