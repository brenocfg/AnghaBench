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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct clock_event_device {int features; int max_delta_ticks; scalar_t__ min_delta_ticks; void* max_delta_ns; void* min_delta_ns; } ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_ONESHOT ; 
 scalar_t__ UINT_MAX ; 
 void* cev_delta2ns (scalar_t__,struct clock_event_device*,int) ; 
 int /*<<< orphan*/  clockevents_calc_mult_shift (struct clock_event_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clockevents_config(struct clock_event_device *dev, u32 freq)
{
	u64 sec;

	if (!(dev->features & CLOCK_EVT_FEAT_ONESHOT))
		return;

	/*
	 * Calculate the maximum number of seconds we can sleep. Limit
	 * to 10 minutes for hardware which can program more than
	 * 32bit ticks so we still get reasonable conversion values.
	 */
	sec = dev->max_delta_ticks;
	do_div(sec, freq);
	if (!sec)
		sec = 1;
	else if (sec > 600 && dev->max_delta_ticks > UINT_MAX)
		sec = 600;

	clockevents_calc_mult_shift(dev, freq, sec);
	dev->min_delta_ns = cev_delta2ns(dev->min_delta_ticks, dev, false);
	dev->max_delta_ns = cev_delta2ns(dev->max_delta_ticks, dev, true);
}