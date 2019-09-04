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
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_3__ {int /*<<< orphan*/  cycle_last; struct clocksource* clock; } ;
struct timekeeper {TYPE_1__ tkr_mono; } ;
struct clocksource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int /*<<< orphan*/  TK_MIRROR ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  clockevents_suspend () ; 
 int /*<<< orphan*/  clocksource_start_suspend_timing (struct clocksource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clocksource_suspend () ; 
 int /*<<< orphan*/  halt_fast_timekeeper (struct timekeeper*) ; 
 int persistent_clock_exists ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_persistent_clock64 (struct timespec64*) ; 
 int suspend_timing_needed ; 
 int /*<<< orphan*/  tick_suspend () ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_forward_now (struct timekeeper*) ; 
 struct timespec64 timekeeping_suspend_time ; 
 int timekeeping_suspended ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int /*<<< orphan*/ ) ; 
 struct timespec64 timespec64_add (struct timespec64,struct timespec64) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 
 TYPE_2__ tk_core ; 
 struct timespec64 tk_xtime (struct timekeeper*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

int timekeeping_suspend(void)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	unsigned long flags;
	struct timespec64		delta, delta_delta;
	static struct timespec64	old_delta;
	struct clocksource *curr_clock;
	u64 cycle_now;

	read_persistent_clock64(&timekeeping_suspend_time);

	/*
	 * On some systems the persistent_clock can not be detected at
	 * timekeeping_init by its return value, so if we see a valid
	 * value returned, update the persistent_clock_exists flag.
	 */
	if (timekeeping_suspend_time.tv_sec || timekeeping_suspend_time.tv_nsec)
		persistent_clock_exists = true;

	suspend_timing_needed = true;

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);
	timekeeping_forward_now(tk);
	timekeeping_suspended = 1;

	/*
	 * Since we've called forward_now, cycle_last stores the value
	 * just read from the current clocksource. Save this to potentially
	 * use in suspend timing.
	 */
	curr_clock = tk->tkr_mono.clock;
	cycle_now = tk->tkr_mono.cycle_last;
	clocksource_start_suspend_timing(curr_clock, cycle_now);

	if (persistent_clock_exists) {
		/*
		 * To avoid drift caused by repeated suspend/resumes,
		 * which each can add ~1 second drift error,
		 * try to compensate so the difference in system time
		 * and persistent_clock time stays close to constant.
		 */
		delta = timespec64_sub(tk_xtime(tk), timekeeping_suspend_time);
		delta_delta = timespec64_sub(delta, old_delta);
		if (abs(delta_delta.tv_sec) >= 2) {
			/*
			 * if delta_delta is too large, assume time correction
			 * has occurred and set old_delta to the current delta.
			 */
			old_delta = delta;
		} else {
			/* Otherwise try to adjust old_system to compensate */
			timekeeping_suspend_time =
				timespec64_add(timekeeping_suspend_time, delta_delta);
		}
	}

	timekeeping_update(tk, TK_MIRROR);
	halt_fast_timekeeper(tk);
	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	tick_suspend();
	clocksource_suspend();
	clockevents_suspend();

	return 0;
}