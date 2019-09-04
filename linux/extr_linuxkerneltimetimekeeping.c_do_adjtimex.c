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
struct TYPE_3__ {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timex {int modes; TYPE_1__ time; } ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timekeeper {scalar_t__ tai_offset; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int ADJ_FREQUENCY ; 
 int ADJ_NANO ; 
 int ADJ_SETOFFSET ; 
 int ADJ_TICK ; 
 int /*<<< orphan*/  TK_ADV_FREQ ; 
 int TK_CLOCK_WAS_SET ; 
 int TK_MIRROR ; 
 int __do_adjtimex (struct timex*,struct timespec64*,scalar_t__*) ; 
 int /*<<< orphan*/  __timekeeping_set_tai_offset (struct timekeeper*,scalar_t__) ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  ntp_notify_cmos_timer () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_advance (int /*<<< orphan*/ ) ; 
 int timekeeping_inject_offset (struct timespec64*) ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 int timekeeping_validate_timex (struct timex*) ; 
 TYPE_2__ tk_core ; 
 int /*<<< orphan*/  tk_update_leap_state (struct timekeeper*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

int do_adjtimex(struct timex *txc)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	unsigned long flags;
	struct timespec64 ts;
	s32 orig_tai, tai;
	int ret;

	/* Validate the data before disabling interrupts */
	ret = timekeeping_validate_timex(txc);
	if (ret)
		return ret;

	if (txc->modes & ADJ_SETOFFSET) {
		struct timespec64 delta;
		delta.tv_sec  = txc->time.tv_sec;
		delta.tv_nsec = txc->time.tv_usec;
		if (!(txc->modes & ADJ_NANO))
			delta.tv_nsec *= 1000;
		ret = timekeeping_inject_offset(&delta);
		if (ret)
			return ret;
	}

	ktime_get_real_ts64(&ts);

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	orig_tai = tai = tk->tai_offset;
	ret = __do_adjtimex(txc, &ts, &tai);

	if (tai != orig_tai) {
		__timekeeping_set_tai_offset(tk, tai);
		timekeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);
	}
	tk_update_leap_state(tk);

	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	/* Update the multiplier immediately if frequency was set directly */
	if (txc->modes & (ADJ_FREQUENCY | ADJ_TICK))
		timekeeping_advance(TK_ADV_FREQ);

	if (tai != orig_tai)
		clock_was_set();

	ntp_notify_cmos_timer();

	return ret;
}