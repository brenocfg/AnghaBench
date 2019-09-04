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
typedef  int u32 ;
struct extif_timings {int clk_div; int* tim; int /*<<< orphan*/  access_time; int /*<<< orphan*/  re_cycle_time; int /*<<< orphan*/  re_off_time; int /*<<< orphan*/  re_on_time; } ;

/* Variables and functions */
 int ps_to_sossi_ticks (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int calc_rd_timings(struct extif_timings *t)
{
	u32 tw0, tw1;
	int reon, reoff, recyc, actim;
	int div = t->clk_div;

	/*
	 * Make sure that after conversion it still holds that:
	 * reoff > reon, recyc >= reoff, actim > reon
	 */
	reon = ps_to_sossi_ticks(t->re_on_time, div);
	/* reon will be exactly one sossi tick */
	if (reon > 1)
		return -1;

	reoff = ps_to_sossi_ticks(t->re_off_time, div);

	if (reoff <= reon)
		reoff = reon + 1;

	tw0 = reoff - reon;
	if (tw0 > 0x10)
		return -1;

	recyc = ps_to_sossi_ticks(t->re_cycle_time, div);
	if (recyc <= reoff)
		recyc = reoff + 1;

	tw1 = recyc - tw0;
	/* values less then 3 result in the SOSSI block resetting itself */
	if (tw1 < 3)
		tw1 = 3;
	if (tw1 > 0x40)
		return -1;

	actim = ps_to_sossi_ticks(t->access_time, div);
	if (actim < reoff)
		actim++;
	/*
	 * access time (data hold time) will be exactly one sossi
	 * tick
	 */
	if (actim - reoff > 1)
		return -1;

	t->tim[0] = tw0 - 1;
	t->tim[1] = tw1 - 1;

	return 0;
}