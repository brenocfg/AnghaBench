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
struct timespec64 {scalar_t__ tv_nsec; } ;
struct timekeeper {int /*<<< orphan*/  wall_to_monotonic; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; struct timekeeper timekeeper; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NSEC_PER_SEC ; 
 int TK_CLEAR_NTP ; 
 int TK_CLOCK_WAS_SET ; 
 int TK_MIRROR ; 
 int /*<<< orphan*/  clock_was_set () ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timekeeper_lock ; 
 int /*<<< orphan*/  timekeeping_forward_now (struct timekeeper*) ; 
 int /*<<< orphan*/  timekeeping_update (struct timekeeper*,int) ; 
 struct timespec64 timespec64_add (int /*<<< orphan*/ ,struct timespec64 const) ; 
 scalar_t__ timespec64_compare (int /*<<< orphan*/ *,struct timespec64 const*) ; 
 int /*<<< orphan*/  timespec64_sub (int /*<<< orphan*/ ,struct timespec64 const) ; 
 int /*<<< orphan*/  timespec64_valid_settod (struct timespec64*) ; 
 TYPE_1__ tk_core ; 
 int /*<<< orphan*/  tk_set_wall_to_mono (struct timekeeper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tk_xtime (struct timekeeper*) ; 
 int /*<<< orphan*/  tk_xtime_add (struct timekeeper*,struct timespec64 const*) ; 
 int /*<<< orphan*/  write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqcount_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timekeeping_inject_offset(const struct timespec64 *ts)
{
	struct timekeeper *tk = &tk_core.timekeeper;
	unsigned long flags;
	struct timespec64 tmp;
	int ret = 0;

	if (ts->tv_nsec < 0 || ts->tv_nsec >= NSEC_PER_SEC)
		return -EINVAL;

	raw_spin_lock_irqsave(&timekeeper_lock, flags);
	write_seqcount_begin(&tk_core.seq);

	timekeeping_forward_now(tk);

	/* Make sure the proposed value is valid */
	tmp = timespec64_add(tk_xtime(tk), *ts);
	if (timespec64_compare(&tk->wall_to_monotonic, ts) > 0 ||
	    !timespec64_valid_settod(&tmp)) {
		ret = -EINVAL;
		goto error;
	}

	tk_xtime_add(tk, ts);
	tk_set_wall_to_mono(tk, timespec64_sub(tk->wall_to_monotonic, *ts));

error: /* even if we error out, we forwarded the time, so call update */
	timekeeping_update(tk, TK_CLEAR_NTP | TK_MIRROR | TK_CLOCK_WAS_SET);

	write_seqcount_end(&tk_core.seq);
	raw_spin_unlock_irqrestore(&timekeeper_lock, flags);

	/* signal hrtimers about time change */
	clock_was_set();

	return ret;
}