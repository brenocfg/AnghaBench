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
struct hrtimer {int dummy; } ;
struct sched_dl_entity {struct hrtimer dl_timer; } ;
struct task_struct {struct sched_dl_entity dl; } ;
struct rq {int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS_HARD ; 
 int /*<<< orphan*/  dl_next_period (struct sched_dl_entity*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  hrtimer_cb_get_time (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_is_queued (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_start (struct hrtimer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 scalar_t__ rq_clock (struct rq*) ; 
 struct rq* task_rq (struct task_struct*) ; 

__attribute__((used)) static int start_dl_timer(struct task_struct *p)
{
	struct sched_dl_entity *dl_se = &p->dl;
	struct hrtimer *timer = &dl_se->dl_timer;
	struct rq *rq = task_rq(p);
	ktime_t now, act;
	s64 delta;

	lockdep_assert_held(&rq->lock);

	/*
	 * We want the timer to fire at the deadline, but considering
	 * that it is actually coming from rq->clock and not from
	 * hrtimer's time base reading.
	 */
	act = ns_to_ktime(dl_next_period(dl_se));
	now = hrtimer_cb_get_time(timer);
	delta = ktime_to_ns(now) - rq_clock(rq);
	act = ktime_add_ns(act, delta);

	/*
	 * If the expiry time already passed, e.g., because the value
	 * chosen as the deadline is too small, don't even try to
	 * start the timer in the past!
	 */
	if (ktime_us_delta(act, now) < 0)
		return 0;

	/*
	 * !enqueued will guarantee another callback; even if one is already in
	 * progress. This ensures a balanced {get,put}_task_struct().
	 *
	 * The race against __run_timer() clearing the enqueued state is
	 * harmless because we're holding task_rq()->lock, therefore the timer
	 * expiring after we've done the check will wait on its task_rq_lock()
	 * and observe our state.
	 */
	if (!hrtimer_is_queued(timer)) {
		get_task_struct(p);
		hrtimer_start(timer, act, HRTIMER_MODE_ABS_HARD);
	}

	return 1;
}