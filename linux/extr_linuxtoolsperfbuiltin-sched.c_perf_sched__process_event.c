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
struct sched_atom {int type; int /*<<< orphan*/  wait_sem; int /*<<< orphan*/  duration; } ;
struct perf_sched {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  SCHED_EVENT_MIGRATION 131 
#define  SCHED_EVENT_RUN 130 
#define  SCHED_EVENT_SLEEP 129 
#define  SCHED_EVENT_WAKEUP 128 
 int /*<<< orphan*/  burn_nsecs (struct perf_sched*,int /*<<< orphan*/ ) ; 
 int sem_post (int /*<<< orphan*/ ) ; 
 int sem_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void perf_sched__process_event(struct perf_sched *sched,
				      struct sched_atom *atom)
{
	int ret = 0;

	switch (atom->type) {
		case SCHED_EVENT_RUN:
			burn_nsecs(sched, atom->duration);
			break;
		case SCHED_EVENT_SLEEP:
			if (atom->wait_sem)
				ret = sem_wait(atom->wait_sem);
			BUG_ON(ret);
			break;
		case SCHED_EVENT_WAKEUP:
			if (atom->wait_sem)
				ret = sem_post(atom->wait_sem);
			BUG_ON(ret);
			break;
		case SCHED_EVENT_MIGRATION:
			break;
		default:
			BUG_ON(1);
	}
}