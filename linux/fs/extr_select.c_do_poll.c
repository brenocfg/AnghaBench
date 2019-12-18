#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct pollfd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * _qproc; } ;
struct poll_wqueues {int error; TYPE_1__ pt; } ;
struct poll_list {int len; struct pollfd* entries; struct poll_list* next; } ;
typedef  TYPE_1__ poll_table ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  scalar_t__ __poll_t ;

/* Variables and functions */
 int ERESTARTNOHAND ; 
 scalar_t__ POLL_BUSY_LOOP ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 unsigned long busy_loop_current_time () ; 
 int /*<<< orphan*/  busy_loop_timeout (unsigned long) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ do_pollfd (struct pollfd*,TYPE_1__*,int*,scalar_t__) ; 
 int /*<<< orphan*/  need_resched () ; 
 scalar_t__ net_busy_loop_on () ; 
 int /*<<< orphan*/  poll_schedule_timeout (struct poll_wqueues*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_estimate_accuracy (struct timespec64*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timespec64_to_ktime (struct timespec64) ; 

__attribute__((used)) static int do_poll(struct poll_list *list, struct poll_wqueues *wait,
		   struct timespec64 *end_time)
{
	poll_table* pt = &wait->pt;
	ktime_t expire, *to = NULL;
	int timed_out = 0, count = 0;
	u64 slack = 0;
	__poll_t busy_flag = net_busy_loop_on() ? POLL_BUSY_LOOP : 0;
	unsigned long busy_start = 0;

	/* Optimise the no-wait case */
	if (end_time && !end_time->tv_sec && !end_time->tv_nsec) {
		pt->_qproc = NULL;
		timed_out = 1;
	}

	if (end_time && !timed_out)
		slack = select_estimate_accuracy(end_time);

	for (;;) {
		struct poll_list *walk;
		bool can_busy_loop = false;

		for (walk = list; walk != NULL; walk = walk->next) {
			struct pollfd * pfd, * pfd_end;

			pfd = walk->entries;
			pfd_end = pfd + walk->len;
			for (; pfd != pfd_end; pfd++) {
				/*
				 * Fish for events. If we found one, record it
				 * and kill poll_table->_qproc, so we don't
				 * needlessly register any other waiters after
				 * this. They'll get immediately deregistered
				 * when we break out and return.
				 */
				if (do_pollfd(pfd, pt, &can_busy_loop,
					      busy_flag)) {
					count++;
					pt->_qproc = NULL;
					/* found something, stop busy polling */
					busy_flag = 0;
					can_busy_loop = false;
				}
			}
		}
		/*
		 * All waiters have already been registered, so don't provide
		 * a poll_table->_qproc to them on the next loop iteration.
		 */
		pt->_qproc = NULL;
		if (!count) {
			count = wait->error;
			if (signal_pending(current))
				count = -ERESTARTNOHAND;
		}
		if (count || timed_out)
			break;

		/* only if found POLL_BUSY_LOOP sockets && not out of time */
		if (can_busy_loop && !need_resched()) {
			if (!busy_start) {
				busy_start = busy_loop_current_time();
				continue;
			}
			if (!busy_loop_timeout(busy_start))
				continue;
		}
		busy_flag = 0;

		/*
		 * If this is the first loop and we have a timeout
		 * given, then we convert to ktime_t and set the to
		 * pointer to the expiry value.
		 */
		if (end_time && !to) {
			expire = timespec64_to_ktime(*end_time);
			to = &expire;
		}

		if (!poll_schedule_timeout(wait, TASK_INTERRUPTIBLE, to, slack))
			timed_out = 1;
	}
	return count;
}