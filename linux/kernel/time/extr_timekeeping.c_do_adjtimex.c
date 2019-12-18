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
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timekeeper {scalar_t__ tai_offset; } ;
struct audit_ntp_data {int dummy; } ;
struct TYPE_3__ {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct __kernel_timex {int modes; TYPE_1__ time; } ;
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
 int __do_adjtimex (struct __kernel_timex*,struct timespec64*,scalar_t__*,struct audit_ntp_data*) ; 
 int /*<<< orphan*/  __timekeeping_set_tai_offset (struct timekeeper*,scalar_t__) ; 
 int /*<<< orphan*/  audit_ntp_init (struct audit_ntp_data*) ; 
 int /*<<< orphan*/  audit_ntp_log (struct audit_ntp_data*) ; 
 int /*<<< orphan*/  audit_tk_injoffset (struct timespec64) ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  ntp_notify_cmos_timer () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_advance (int /*<<< orphan*/ ) ; 
 int timekeeping_inject_offset (struct timespec64*) ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 int timekeeping_validate_timex (struct __kernel_timex*) ; 
 TYPE_2__ tk_core ; 
 int /*<<< orphan*/  tk_update_leap_state (struct timekeeper*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

int do_adjtimex(struct __kernel_timex *txc)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	struct audit_ntp_data ad;
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

		audit_tk_injoffset(delta);
	}

	audit_ntp_init(&ad);

	ktime_get_real_ts64(&ts);

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	orig_tai = tai = tk->tai_offset;
	ret = __do_adjtimex(txc, &ts, &tai, &ad);

	if (tai != orig_tai) {
		__timekeeping_set_tai_offset(tk, tai);
		timekeeping_update(tk, TK_MIRROR | TK_CLOCK_WAS_SET);
	}
	tk_update_leap_state(tk);

	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	audit_ntp_log(&ad);

	/* Update the multiplier immediately if frequency was set directly */
	if (txc->modes & (ADJ_FREQUENCY | ADJ_TICK))
		timekeeping_advance(TK_ADV_FREQ);

	if (tai != orig_tai)
		clock_was_set();

	ntp_notify_cmos_timer();

	return ret;
}