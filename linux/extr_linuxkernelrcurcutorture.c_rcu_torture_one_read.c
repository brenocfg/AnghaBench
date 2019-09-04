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
struct torture_random_state {int dummy; } ;
struct rcu_torture {scalar_t__ rtort_mbtest; int rtort_pipe_count; int /*<<< orphan*/  rtort_rcu; } ;
struct TYPE_2__ {unsigned long (* get_gp_seq ) () ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_ALL ; 
 int RCUTORTURE_RDR_MASK ; 
 int RCU_TORTURE_PIPE_LEN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/  do_trace_rcu_torture_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  n_rcu_torture_mberror ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct rcu_torture* rcu_dereference_check (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_ftrace_dump (int /*<<< orphan*/ ) ; 
 scalar_t__ rcu_read_lock_bh_held () ; 
 scalar_t__ rcu_read_lock_sched_held () ; 
 int /*<<< orphan*/ * rcu_torture_batch ; 
 int /*<<< orphan*/ * rcu_torture_count ; 
 int /*<<< orphan*/  rcu_torture_current ; 
 unsigned long long rcu_trace_clock_local () ; 
 int rcutorture_extend_mask (int,struct torture_random_state*) ; 
 int /*<<< orphan*/  rcutorture_loop_extend (int*,struct torture_random_state*) ; 
 int /*<<< orphan*/  rcutorture_one_extend (int*,int,struct torture_random_state*) ; 
 unsigned long rcutorture_seq_diff (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  srcu_ctlp ; 
 scalar_t__ srcu_read_lock_held (int /*<<< orphan*/ ) ; 
 unsigned long stub1 () ; 
 unsigned long stub2 () ; 
 scalar_t__ torturing_tasks () ; 

__attribute__((used)) static bool rcu_torture_one_read(struct torture_random_state *trsp)
{
	unsigned long started;
	unsigned long completed;
	int newstate;
	struct rcu_torture *p;
	int pipe_count;
	int readstate = 0;
	unsigned long long ts;

	newstate = rcutorture_extend_mask(readstate, trsp);
	rcutorture_one_extend(&readstate, newstate, trsp);
	started = cur_ops->get_gp_seq();
	ts = rcu_trace_clock_local();
	p = rcu_dereference_check(rcu_torture_current,
				  rcu_read_lock_bh_held() ||
				  rcu_read_lock_sched_held() ||
				  srcu_read_lock_held(srcu_ctlp) ||
				  torturing_tasks());
	if (p == NULL) {
		/* Wait for rcu_torture_writer to get underway */
		rcutorture_one_extend(&readstate, 0, trsp);
		return false;
	}
	if (p->rtort_mbtest == 0)
		atomic_inc(&n_rcu_torture_mberror);
	rcutorture_loop_extend(&readstate, trsp);
	preempt_disable();
	pipe_count = p->rtort_pipe_count;
	if (pipe_count > RCU_TORTURE_PIPE_LEN) {
		/* Should not happen, but... */
		pipe_count = RCU_TORTURE_PIPE_LEN;
	}
	completed = cur_ops->get_gp_seq();
	if (pipe_count > 1) {
		do_trace_rcu_torture_read(cur_ops->name, &p->rtort_rcu,
					  ts, started, completed);
		rcu_ftrace_dump(DUMP_ALL);
	}
	__this_cpu_inc(rcu_torture_count[pipe_count]);
	completed = rcutorture_seq_diff(completed, started);
	if (completed > RCU_TORTURE_PIPE_LEN) {
		/* Should not happen, but... */
		completed = RCU_TORTURE_PIPE_LEN;
	}
	__this_cpu_inc(rcu_torture_batch[completed]);
	preempt_enable();
	rcutorture_one_extend(&readstate, 0, trsp);
	WARN_ON_ONCE(readstate & RCUTORTURE_RDR_MASK);
	return true;
}