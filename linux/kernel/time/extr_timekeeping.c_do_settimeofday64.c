#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct timekeeper {int /*<<< orphan*/  wall_to_monotonic; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int EINVAL ; 
 int TK_CLEAR_NTP ; 
 int TK_CLOCK_WAS_SET ; 
 int TK_MIRROR ; 
 int /*<<< orphan*/  audit_tk_injoffset (struct timespec64) ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_forward_now (struct timekeeper*) ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 scalar_t__ timespec64_compare (int /*<<< orphan*/ *,struct timespec64*) ; 
 int /*<<< orphan*/  timespec64_sub (int /*<<< orphan*/ ,struct timespec64) ; 
 int /*<<< orphan*/  timespec64_valid_settod (struct timespec64 const*) ; 
 TYPE_1__ tk_core ; 
 int /*<<< orphan*/  tk_set_wall_to_mono (struct timekeeper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tk_set_xtime (struct timekeeper*,struct timespec64 const*) ; 
 struct timespec64 tk_xtime (struct timekeeper*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

int do_settimeofday64(const struct timespec64 *ts)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	struct timespec64 ts_delta, xt;
	unsigned long flags;
	int ret = 0;

	if (!timespec64_valid_settod(ts))
		return -EINVAL;

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	timekeeping_forward_now(tk);

	xt = tk_xtime(tk);
	ts_delta.tv_sec = ts->tv_sec - xt.tv_sec;
	ts_delta.tv_nsec = ts->tv_nsec - xt.tv_nsec;

	if (timespec64_compare(&tk->wall_to_monotonic, &ts_delta) > 0) {
		ret = -EINVAL;
		goto out;
	}

	tk_set_wall_to_mono(tk, timespec64_sub(tk->wall_to_monotonic, ts_delta));

	tk_set_xtime(tk, ts);
out:
	timekeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	/* signal hrtimers about time change */
	clock_was_set();

	if (!ret)
		audit_tk_injoffset(ts_delta);

	return ret;
}