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
typedef  int u32 ;
struct clocksource {int mask; int mult; int maxadj; int /*<<< orphan*/  max_idle_ns; int /*<<< orphan*/  max_cycles; int /*<<< orphan*/  name; int /*<<< orphan*/  shift; } ;

/* Variables and functions */
 int NSEC_PER_SEC ; 
 scalar_t__ UINT_MAX ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocks_calc_mult_shift (int*,int /*<<< orphan*/ *,int,int,int) ; 
 void* clocksource_max_adjustment (struct clocksource*) ; 
 int /*<<< orphan*/  clocksource_update_max_deferment (struct clocksource*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __clocksource_update_freq_scale(struct clocksource *cs, u32 scale, u32 freq)
{
	u64 sec;

	/*
	 * Default clocksources are *special* and self-define their mult/shift.
	 * But, you're not special, so you should specify a freq value.
	 */
	if (freq) {
		/*
		 * Calc the maximum number of seconds which we can run before
		 * wrapping around. For clocksources which have a mask > 32-bit
		 * we need to limit the max sleep time to have a good
		 * conversion precision. 10 minutes is still a reasonable
		 * amount. That results in a shift value of 24 for a
		 * clocksource with mask >= 40-bit and f >= 4GHz. That maps to
		 * ~ 0.06ppm granularity for NTP.
		 */
		sec = cs->mask;
		do_div(sec, freq);
		do_div(sec, scale);
		if (!sec)
			sec = 1;
		else if (sec > 600 && cs->mask > UINT_MAX)
			sec = 600;

		clocks_calc_mult_shift(&cs->mult, &cs->shift, freq,
				       NSEC_PER_SEC / scale, sec * scale);
	}
	/*
	 * Ensure clocksources that have large 'mult' values don't overflow
	 * when adjusted.
	 */
	cs->maxadj = clocksource_max_adjustment(cs);
	while (freq && ((cs->mult + cs->maxadj < cs->mult)
		|| (cs->mult - cs->maxadj > cs->mult))) {
		cs->mult >>= 1;
		cs->shift--;
		cs->maxadj = clocksource_max_adjustment(cs);
	}

	/*
	 * Only warn for *special* clocksources that self-define
	 * their mult/shift values and don't specify a freq.
	 */
	WARN_ONCE(cs->mult + cs->maxadj < cs->mult,
		"timekeeping: Clocksource %s might overflow on 11%% adjustment\n",
		cs->name);

	clocksource_update_max_deferment(cs);

	pr_info("%s: mask: 0x%llx max_cycles: 0x%llx, max_idle_ns: %lld ns\n",
		cs->name, cs->mask, cs->max_cycles, cs->max_idle_ns);
}