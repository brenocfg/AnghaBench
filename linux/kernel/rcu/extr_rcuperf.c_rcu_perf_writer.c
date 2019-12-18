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
typedef  void* u64 ;
struct sched_param {int sched_priority; } ;
struct rcu_head {int dummy; } ;
struct TYPE_2__ {int (* exp_completed ) () ;int (* get_gp_seq ) () ;int /*<<< orphan*/  (* gp_barrier ) () ;int /*<<< orphan*/  (* sync ) () ;int /*<<< orphan*/  (* exp_sync ) () ;int /*<<< orphan*/  (* async ) (struct rcu_head*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_ALL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int MAX_MEAS ; 
 int MIN_MEAS ; 
 int /*<<< orphan*/  PERFOUT_STRING (char*) ; 
 int /*<<< orphan*/  PERF_FLAG ; 
 int /*<<< orphan*/  RTWS_ASYNC ; 
 int /*<<< orphan*/  RTWS_BARRIER ; 
 int /*<<< orphan*/  RTWS_EXP_SYNC ; 
 int /*<<< orphan*/  RTWS_IDLE ; 
 int /*<<< orphan*/  RTWS_STOPPING ; 
 int /*<<< orphan*/  RTWS_SYNC ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SCHED_NORMAL ; 
 scalar_t__ SYSTEM_RUNNING ; 
 int /*<<< orphan*/  VERBOSE_PERFOUT_STRING (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int b_rcu_perf_writer_finished ; 
 int b_rcu_perf_writer_started ; 
 int /*<<< orphan*/  cpumask_of (long) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ gp_async ; 
 scalar_t__ gp_async_max ; 
 scalar_t__ gp_exp ; 
 int holdoff ; 
 int /*<<< orphan*/  kfree (struct rcu_head*) ; 
 struct rcu_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 void* ktime_get_mono_fast_ns () ; 
 int /*<<< orphan*/  n_async_inflight ; 
 int /*<<< orphan*/  n_rcu_perf_writer_finished ; 
 int /*<<< orphan*/  n_rcu_perf_writer_started ; 
 long nr_cpu_ids ; 
 scalar_t__ nrealwriters ; 
 int /*<<< orphan*/  perf_type ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int) ; 
 int /*<<< orphan*/  rcu_ftrace_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_perf_async_cb ; 
 int /*<<< orphan*/  rcu_perf_wait_shutdown () ; 
 int /*<<< orphan*/  rcu_perf_writer_state ; 
 int /*<<< orphan*/  sched_setscheduler_nocheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown ; 
 int /*<<< orphan*/  shutdown_wq ; 
 int /*<<< orphan*/  smp_mb () ; 
 int stub1 () ; 
 int stub2 () ; 
 int /*<<< orphan*/  stub3 (struct rcu_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 () ; 
 int /*<<< orphan*/  stub5 () ; 
 int /*<<< orphan*/  stub6 () ; 
 int stub7 () ; 
 int stub8 () ; 
 int /*<<< orphan*/  stub9 () ; 
 scalar_t__ system_state ; 
 void* t_rcu_perf_writer_finished ; 
 void* t_rcu_perf_writer_started ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  torture_kthread_stopping (char*) ; 
 int /*<<< orphan*/  torture_must_stop () ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 void*** writer_durations ; 
 scalar_t__ writer_holdoff ; 
 int* writer_n_durations ; 

__attribute__((used)) static int
rcu_perf_writer(void *arg)
{
	int i = 0;
	int i_max;
	long me = (long)arg;
	struct rcu_head *rhp = NULL;
	struct sched_param sp;
	bool started = false, done = false, alldone = false;
	u64 t;
	u64 *wdp;
	u64 *wdpp = writer_durations[me];

	VERBOSE_PERFOUT_STRING("rcu_perf_writer task started");
	WARN_ON(!wdpp);
	set_cpus_allowed_ptr(current, cpumask_of(me % nr_cpu_ids));
	sp.sched_priority = 1;
	sched_setscheduler_nocheck(current, SCHED_FIFO, &sp);

	if (holdoff)
		schedule_timeout_uninterruptible(holdoff * HZ);

	/*
	 * Wait until rcu_end_inkernel_boot() is called for normal GP tests
	 * so that RCU is not always expedited for normal GP tests.
	 * The system_state test is approximate, but works well in practice.
	 */
	while (!gp_exp && system_state != SYSTEM_RUNNING)
		schedule_timeout_uninterruptible(1);

	t = ktime_get_mono_fast_ns();
	if (atomic_inc_return(&n_rcu_perf_writer_started) >= nrealwriters) {
		t_rcu_perf_writer_started = t;
		if (gp_exp) {
			b_rcu_perf_writer_started =
				cur_ops->exp_completed() / 2;
		} else {
			b_rcu_perf_writer_started = cur_ops->get_gp_seq();
		}
	}

	do {
		if (writer_holdoff)
			udelay(writer_holdoff);
		wdp = &wdpp[i];
		*wdp = ktime_get_mono_fast_ns();
		if (gp_async) {
retry:
			if (!rhp)
				rhp = kmalloc(sizeof(*rhp), GFP_KERNEL);
			if (rhp && atomic_read(this_cpu_ptr(&n_async_inflight)) < gp_async_max) {
				rcu_perf_writer_state = RTWS_ASYNC;
				atomic_inc(this_cpu_ptr(&n_async_inflight));
				cur_ops->async(rhp, rcu_perf_async_cb);
				rhp = NULL;
			} else if (!kthread_should_stop()) {
				rcu_perf_writer_state = RTWS_BARRIER;
				cur_ops->gp_barrier();
				goto retry;
			} else {
				kfree(rhp); /* Because we are stopping. */
			}
		} else if (gp_exp) {
			rcu_perf_writer_state = RTWS_EXP_SYNC;
			cur_ops->exp_sync();
		} else {
			rcu_perf_writer_state = RTWS_SYNC;
			cur_ops->sync();
		}
		rcu_perf_writer_state = RTWS_IDLE;
		t = ktime_get_mono_fast_ns();
		*wdp = t - *wdp;
		i_max = i;
		if (!started &&
		    atomic_read(&n_rcu_perf_writer_started) >= nrealwriters)
			started = true;
		if (!done && i >= MIN_MEAS) {
			done = true;
			sp.sched_priority = 0;
			sched_setscheduler_nocheck(current,
						   SCHED_NORMAL, &sp);
			pr_alert("%s%s rcu_perf_writer %ld has %d measurements\n",
				 perf_type, PERF_FLAG, me, MIN_MEAS);
			if (atomic_inc_return(&n_rcu_perf_writer_finished) >=
			    nrealwriters) {
				schedule_timeout_interruptible(10);
				rcu_ftrace_dump(DUMP_ALL);
				PERFOUT_STRING("Test complete");
				t_rcu_perf_writer_finished = t;
				if (gp_exp) {
					b_rcu_perf_writer_finished =
						cur_ops->exp_completed() / 2;
				} else {
					b_rcu_perf_writer_finished =
						cur_ops->get_gp_seq();
				}
				if (shutdown) {
					smp_mb(); /* Assign before wake. */
					wake_up(&shutdown_wq);
				}
			}
		}
		if (done && !alldone &&
		    atomic_read(&n_rcu_perf_writer_finished) >= nrealwriters)
			alldone = true;
		if (started && !alldone && i < MAX_MEAS - 1)
			i++;
		rcu_perf_wait_shutdown();
	} while (!torture_must_stop());
	if (gp_async) {
		rcu_perf_writer_state = RTWS_BARRIER;
		cur_ops->gp_barrier();
	}
	rcu_perf_writer_state = RTWS_STOPPING;
	writer_n_durations[me] = i_max;
	torture_kthread_stopping("rcu_perf_writer");
	return 0;
}