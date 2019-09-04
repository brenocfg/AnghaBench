#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct timespec64 {int dummy; } ;
struct TYPE_4__ {scalar_t__ cycle_last; } ;
struct TYPE_6__ {scalar_t__ cycle_last; struct clocksource* clock; } ;
struct timekeeper {scalar_t__ ntp_error; TYPE_1__ tkr_raw; TYPE_3__ tkr_mono; } ;
struct clocksource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int TK_CLOCK_WAS_SET ; 
 int TK_MIRROR ; 
 int /*<<< orphan*/  __timekeeping_inject_sleeptime (struct timekeeper*,struct timespec64*) ; 
 int /*<<< orphan*/  clockevents_resume () ; 
 int /*<<< orphan*/  clocksource_resume () ; 
 scalar_t__ clocksource_stop_suspend_timing (struct clocksource*,scalar_t__) ; 
 int /*<<< orphan*/  hrtimers_resume () ; 
 struct timespec64 ns_to_timespec64 (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_persistent_clock64 (struct timespec64*) ; 
 int suspend_timing_needed ; 
 int /*<<< orphan*/  tick_resume () ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_suspend_time ; 
 scalar_t__ timekeeping_suspended ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 scalar_t__ timespec64_compare (struct timespec64*,int /*<<< orphan*/ *) ; 
 struct timespec64 timespec64_sub (struct timespec64,int /*<<< orphan*/ ) ; 
 scalar_t__ tk_clock_read (TYPE_3__*) ; 
 TYPE_2__ tk_core ; 
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

void timekeeping_resume(void)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	struct clocksource *clock = tk->tkr_mono.clock;
	unsigned long flags;
	struct timespec64 ts_new, ts_delta;
	u64 cycle_now, nsec;
	bool inject_sleeptime = false;

	read_persistent_clock64(&ts_new);

	clockevents_resume();
	clocksource_resume();

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	/*
	 * After system resumes, we need to calculate the suspended time and
	 * compensate it for the OS time. There are 3 sources that could be
	 * used: Nonstop clocksource during suspend, persistent clock and rtc
	 * device.
	 *
	 * One specific platform may have 1 or 2 or all of them, and the
	 * preference will be:
	 *	suspend-nonstop clocksource -> persistent clock -> rtc
	 * The less preferred source will only be tried if there is no better
	 * usable source. The rtc part is handled separately in rtc core code.
	 */
	cycle_now = tk_clock_read(&tk->tkr_mono);
	nsec = clocksource_stop_suspend_timing(clock, cycle_now);
	if (nsec > 0) {
		ts_delta = ns_to_timespec64(nsec);
		inject_sleeptime = true;
	} else if (timespec64_compare(&ts_new, &timekeeping_suspend_time) > 0) {
		ts_delta = timespec64_sub(ts_new, timekeeping_suspend_time);
		inject_sleeptime = true;
	}

	if (inject_sleeptime) {
		suspend_timing_needed = false;
		__timekeeping_inject_sleeptime(tk, &ts_delta);
	}

	/* Re-base the last cycle value */
	tk->tkr_mono.cycle_last = cycle_now;
	tk->tkr_raw.cycle_last  = cycle_now;

	tk->ntp_error = 0;
	timekeeping_suspended = 0;
	timekeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);
	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	touch_softlockup_watchdog();

	tick_resume();
	hrtimers_resume();
}