#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_6__ {scalar_t__ timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  sum_exec_runtime; } ;
struct task_cputime {void* sched_exp; void* virt_exp; void* prof_exp; } ;
struct task_struct {int /*<<< orphan*/  comm; TYPE_4__* signal; TYPE_2__ rt; TYPE_1__ se; struct task_cputime cputime_expires; struct list_head* cpu_timers; } ;
struct list_head {int dummy; } ;
struct TYPE_8__ {TYPE_3__* rlim; } ;
struct TYPE_7__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned long,unsigned long) ; 
 unsigned long HZ ; 
 size_t RLIMIT_RTTIME ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  TICK_DEP_BIT_POSIX_TIMER ; 
 unsigned long USEC_PER_SEC ; 
 int /*<<< orphan*/  __group_send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  check_dl_overrun (struct task_struct*) ; 
 void* check_timers_list (struct list_head*,struct list_head*,int /*<<< orphan*/ ) ; 
 scalar_t__ dl_task (struct task_struct*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ print_fatal_signals ; 
 int /*<<< orphan*/  prof_ticks (struct task_struct*) ; 
 scalar_t__ task_cputime_zero (struct task_cputime*) ; 
 int /*<<< orphan*/  task_pid_nr (struct task_struct*) ; 
 unsigned long task_rlimit (struct task_struct*,size_t) ; 
 unsigned long task_rlimit_max (struct task_struct*,size_t) ; 
 int /*<<< orphan*/  tick_dep_clear_task (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_ticks (struct task_struct*) ; 

__attribute__((used)) static void check_thread_timers(struct task_struct *tsk,
				struct list_head *firing)
{
	struct list_head *timers = tsk->cpu_timers;
	struct task_cputime *tsk_expires = &tsk->cputime_expires;
	u64 expires;
	unsigned long soft;

	if (dl_task(tsk))
		check_dl_overrun(tsk);

	/*
	 * If cputime_expires is zero, then there are no active
	 * per thread CPU timers.
	 */
	if (task_cputime_zero(&tsk->cputime_expires))
		return;

	expires = check_timers_list(timers, firing, prof_ticks(tsk));
	tsk_expires->prof_exp = expires;

	expires = check_timers_list(++timers, firing, virt_ticks(tsk));
	tsk_expires->virt_exp = expires;

	tsk_expires->sched_exp = check_timers_list(++timers, firing,
						   tsk->se.sum_exec_runtime);

	/*
	 * Check for the special case thread timers.
	 */
	soft = task_rlimit(tsk, RLIMIT_RTTIME);
	if (soft != RLIM_INFINITY) {
		unsigned long hard = task_rlimit_max(tsk, RLIMIT_RTTIME);

		if (hard != RLIM_INFINITY &&
		    tsk->rt.timeout > DIV_ROUND_UP(hard, USEC_PER_SEC/HZ)) {
			/*
			 * At the hard limit, we just die.
			 * No need to calculate anything else now.
			 */
			if (print_fatal_signals) {
				pr_info("CPU Watchdog Timeout (hard): %s[%d]\n",
					tsk->comm, task_pid_nr(tsk));
			}
			__group_send_sig_info(SIGKILL, SEND_SIG_PRIV, tsk);
			return;
		}
		if (tsk->rt.timeout > DIV_ROUND_UP(soft, USEC_PER_SEC/HZ)) {
			/*
			 * At the soft limit, send a SIGXCPU every second.
			 */
			if (soft < hard) {
				soft += USEC_PER_SEC;
				tsk->signal->rlim[RLIMIT_RTTIME].rlim_cur =
					soft;
			}
			if (print_fatal_signals) {
				pr_info("RT Watchdog Timeout (soft): %s[%d]\n",
					tsk->comm, task_pid_nr(tsk));
			}
			__group_send_sig_info(SIGXCPU, SEND_SIG_PRIV, tsk);
		}
	}
	if (task_cputime_zero(tsk_expires))
		tick_dep_clear_task(tsk, TICK_DEP_BIT_POSIX_TIMER);
}