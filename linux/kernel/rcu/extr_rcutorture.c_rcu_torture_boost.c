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
struct sched_param {int sched_priority; } ;
struct rcu_boost_inflight {int /*<<< orphan*/  rcu; int /*<<< orphan*/  inflight; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 scalar_t__ ULONG_CMP_LT (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  boost_mutex ; 
 unsigned long boost_starttime ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  destroy_rcu_head_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rcu_head_on_stack (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_rcu_torture_boost_rterror ; 
 int /*<<< orphan*/  n_rcu_torture_boosts ; 
 int /*<<< orphan*/  rcu_torture_boost_cb ; 
 scalar_t__ rcu_torture_boost_failed (unsigned long,unsigned long) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (unsigned long) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stutter_wait (char*) ; 
 unsigned long test_boost_duration ; 
 unsigned long test_boost_interval ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 scalar_t__ torture_must_stop () ; 
 int /*<<< orphan*/  torture_shutdown_absorb (char*) ; 

__attribute__((used)) static int rcu_torture_boost(void *arg)
{
	unsigned long call_rcu_time;
	unsigned long endtime;
	unsigned long oldstarttime;
	struct rcu_boost_inflight rbi = { .inflight = 0 };
	struct sched_param sp;

	VERBOSE_TOROUT_STRING("rcu_torture_boost started");

	/* Set real-time priority. */
	sp.sched_priority = 1;
	if (sched_setscheduler(current, SCHED_FIFO, &sp) < 0) {
		VERBOSE_TOROUT_STRING("rcu_torture_boost RT prio failed!");
		n_rcu_torture_boost_rterror++;
	}

	init_rcu_head_on_stack(&rbi.rcu);
	/* Each pass through the following loop does one boost-test cycle. */
	do {
		/* Track if the test failed already in this test interval? */
		bool failed = false;

		/* Increment n_rcu_torture_boosts once per boost-test */
		while (!kthread_should_stop()) {
			if (mutex_trylock(&boost_mutex)) {
				n_rcu_torture_boosts++;
				mutex_unlock(&boost_mutex);
				break;
			}
			schedule_timeout_uninterruptible(1);
		}
		if (kthread_should_stop())
			goto checkwait;

		/* Wait for the next test interval. */
		oldstarttime = boost_starttime;
		while (ULONG_CMP_LT(jiffies, oldstarttime)) {
			schedule_timeout_interruptible(oldstarttime - jiffies);
			stutter_wait("rcu_torture_boost");
			if (torture_must_stop())
				goto checkwait;
		}

		/* Do one boost-test interval. */
		endtime = oldstarttime + test_boost_duration * HZ;
		call_rcu_time = jiffies;
		while (ULONG_CMP_LT(jiffies, endtime)) {
			/* If we don't have a callback in flight, post one. */
			if (!smp_load_acquire(&rbi.inflight)) {
				/* RCU core before ->inflight = 1. */
				smp_store_release(&rbi.inflight, 1);
				call_rcu(&rbi.rcu, rcu_torture_boost_cb);
				/* Check if the boost test failed */
				failed = failed ||
					 rcu_torture_boost_failed(call_rcu_time,
								 jiffies);
				call_rcu_time = jiffies;
			}
			stutter_wait("rcu_torture_boost");
			if (torture_must_stop())
				goto checkwait;
		}

		/*
		 * If boost never happened, then inflight will always be 1, in
		 * this case the boost check would never happen in the above
		 * loop so do another one here.
		 */
		if (!failed && smp_load_acquire(&rbi.inflight))
			rcu_torture_boost_failed(call_rcu_time, jiffies);

		/*
		 * Set the start time of the next test interval.
		 * Yes, this is vulnerable to long delays, but such
		 * delays simply cause a false negative for the next
		 * interval.  Besides, we are running at RT priority,
		 * so delays should be relatively rare.
		 */
		while (oldstarttime == boost_starttime &&
		       !kthread_should_stop()) {
			if (mutex_trylock(&boost_mutex)) {
				boost_starttime = jiffies +
						  test_boost_interval * HZ;
				mutex_unlock(&boost_mutex);
				break;
			}
			schedule_timeout_uninterruptible(1);
		}

		/* Go do the stutter. */
checkwait:	stutter_wait("rcu_torture_boost");
	} while (!torture_must_stop());

	/* Clean up and exit. */
	while (!kthread_should_stop() || smp_load_acquire(&rbi.inflight)) {
		torture_shutdown_absorb("rcu_torture_boost");
		schedule_timeout_uninterruptible(1);
	}
	destroy_rcu_head_on_stack(&rbi.rcu);
	torture_kthread_stopping("rcu_torture_boost");
	return 0;
}