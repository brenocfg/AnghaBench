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
typedef  void* u64 ;
struct user_namespace {int dummy; } ;
struct taskstats {int /*<<< orphan*/  ac_comm; int /*<<< orphan*/  ac_majflt; int /*<<< orphan*/  ac_minflt; void* ac_stimescaled; void* ac_utimescaled; void* ac_stime; void* ac_utime; int /*<<< orphan*/  ac_ppid; int /*<<< orphan*/  ac_gid; int /*<<< orphan*/  ac_uid; int /*<<< orphan*/  ac_pid; int /*<<< orphan*/  ac_sched; int /*<<< orphan*/  ac_nice; int /*<<< orphan*/  ac_flag; int /*<<< orphan*/  ac_exitcode; void* ac_btime; void* ac_etime; } ;
struct task_struct {int flags; int /*<<< orphan*/  comm; int /*<<< orphan*/  maj_flt; int /*<<< orphan*/  min_flt; int /*<<< orphan*/  real_parent; int /*<<< orphan*/  policy; int /*<<< orphan*/  exit_code; void* start_time; } ;
struct pid_namespace {int dummy; } ;
struct cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACORE ; 
 int /*<<< orphan*/  AFORK ; 
 int /*<<< orphan*/  ASU ; 
 int /*<<< orphan*/  AXSIG ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 int PF_DUMPCORE ; 
 int PF_FORKNOEXEC ; 
 int PF_SIGNALED ; 
 int PF_SUPERPRIV ; 
 scalar_t__ TASK_COMM_LEN ; 
 scalar_t__ TS_COMM_LEN ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 struct cred* __task_cred (struct task_struct*) ; 
 void* div_u64 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kgid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 void* get_seconds () ; 
 void* ktime_get_ns () ; 
 scalar_t__ pid_alive (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_cputime (struct task_struct*,void**,void**) ; 
 int /*<<< orphan*/  task_cputime_scaled (struct task_struct*,void**,void**) ; 
 int /*<<< orphan*/  task_nice (struct task_struct*) ; 
 int /*<<< orphan*/  task_pid_nr_ns (struct task_struct*,struct pid_namespace*) ; 
 int /*<<< orphan*/  task_tgid_nr_ns (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 

void bacct_add_tsk(struct user_namespace *user_ns,
		   struct pid_namespace *pid_ns,
		   struct taskstats *stats, struct task_struct *tsk)
{
	const struct cred *tcred;
	u64 utime, stime, utimescaled, stimescaled;
	u64 delta;

	BUILD_BUG_ON(TS_COMM_LEN < TASK_COMM_LEN);

	/* calculate task elapsed time in nsec */
	delta = ktime_get_ns() - tsk->start_time;
	/* Convert to micro seconds */
	do_div(delta, NSEC_PER_USEC);
	stats->ac_etime = delta;
	/* Convert to seconds for btime */
	do_div(delta, USEC_PER_SEC);
	stats->ac_btime = get_seconds() - delta;
	if (thread_group_leader(tsk)) {
		stats->ac_exitcode = tsk->exit_code;
		if (tsk->flags & PF_FORKNOEXEC)
			stats->ac_flag |= AFORK;
	}
	if (tsk->flags & PF_SUPERPRIV)
		stats->ac_flag |= ASU;
	if (tsk->flags & PF_DUMPCORE)
		stats->ac_flag |= ACORE;
	if (tsk->flags & PF_SIGNALED)
		stats->ac_flag |= AXSIG;
	stats->ac_nice	 = task_nice(tsk);
	stats->ac_sched	 = tsk->policy;
	stats->ac_pid	 = task_pid_nr_ns(tsk, pid_ns);
	rcu_read_lock();
	tcred = __task_cred(tsk);
	stats->ac_uid	 = from_kuid_munged(user_ns, tcred->uid);
	stats->ac_gid	 = from_kgid_munged(user_ns, tcred->gid);
	stats->ac_ppid	 = pid_alive(tsk) ?
		task_tgid_nr_ns(rcu_dereference(tsk->real_parent), pid_ns) : 0;
	rcu_read_unlock();

	task_cputime(tsk, &utime, &stime);
	stats->ac_utime = div_u64(utime, NSEC_PER_USEC);
	stats->ac_stime = div_u64(stime, NSEC_PER_USEC);

	task_cputime_scaled(tsk, &utimescaled, &stimescaled);
	stats->ac_utimescaled = div_u64(utimescaled, NSEC_PER_USEC);
	stats->ac_stimescaled = div_u64(stimescaled, NSEC_PER_USEC);

	stats->ac_minflt = tsk->min_flt;
	stats->ac_majflt = tsk->maj_flt;

	strncpy(stats->ac_comm, tsk->comm, sizeof(stats->ac_comm));
}