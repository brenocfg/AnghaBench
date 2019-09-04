#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {unsigned int period; unsigned int duty_cycle; } ;
struct meson_pwm_channel {unsigned int pre_div; unsigned int hi; unsigned int lo; int /*<<< orphan*/  clk; TYPE_1__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct meson_pwm {unsigned int inverter_mask; TYPE_2__ chip; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int EINVAL ; 
 unsigned int MISC_CLK_DIV_MASK ; 
 scalar_t__ NSEC_PER_SEC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (int,unsigned long) ; 

__attribute__((used)) static int meson_pwm_calc(struct meson_pwm *meson,
			  struct meson_pwm_channel *channel, unsigned int id,
			  unsigned int duty, unsigned int period)
{
	unsigned int pre_div, cnt, duty_cnt;
	unsigned long fin_freq = -1;
	u64 fin_ps;

	if (~(meson->inverter_mask >> id) & 0x1)
		duty = period - duty;

	if (period == channel->state.period &&
	    duty == channel->state.duty_cycle)
		return 0;

	fin_freq = clk_get_rate(channel->clk);
	if (fin_freq == 0) {
		dev_err(meson->chip.dev, "invalid source clock frequency\n");
		return -EINVAL;
	}

	dev_dbg(meson->chip.dev, "fin_freq: %lu Hz\n", fin_freq);
	fin_ps = (u64)NSEC_PER_SEC * 1000;
	do_div(fin_ps, fin_freq);

	/* Calc pre_div with the period */
	for (pre_div = 0; pre_div < MISC_CLK_DIV_MASK; pre_div++) {
		cnt = DIV_ROUND_CLOSEST_ULL((u64)period * 1000,
					    fin_ps * (pre_div + 1));
		dev_dbg(meson->chip.dev, "fin_ps=%llu pre_div=%u cnt=%u\n",
			fin_ps, pre_div, cnt);
		if (cnt <= 0xffff)
			break;
	}

	if (pre_div == MISC_CLK_DIV_MASK) {
		dev_err(meson->chip.dev, "unable to get period pre_div\n");
		return -EINVAL;
	}

	dev_dbg(meson->chip.dev, "period=%u pre_div=%u cnt=%u\n", period,
		pre_div, cnt);

	if (duty == period) {
		channel->pre_div = pre_div;
		channel->hi = cnt;
		channel->lo = 0;
	} else if (duty == 0) {
		channel->pre_div = pre_div;
		channel->hi = 0;
		channel->lo = cnt;
	} else {
		/* Then check is we can have the duty with the same pre_div */
		duty_cnt = DIV_ROUND_CLOSEST_ULL((u64)duty * 1000,
						 fin_ps * (pre_div + 1));
		if (duty_cnt > 0xffff) {
			dev_err(meson->chip.dev, "unable to get duty cycle\n");
			return -EINVAL;
		}

		dev_dbg(meson->chip.dev, "duty=%u pre_div=%u duty_cnt=%u\n",
			duty, pre_div, duty_cnt);

		channel->pre_div = pre_div;
		channel->hi = duty_cnt;
		channel->lo = cnt - duty_cnt;
	}

	return 0;
}