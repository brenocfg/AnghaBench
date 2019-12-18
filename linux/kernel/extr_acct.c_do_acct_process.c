#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pid_namespace {int dummy; } ;
struct file {TYPE_6__* f_cred; } ;
struct cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct bsd_acct_struct {struct pid_namespace* ns; struct file* file; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_12__ {void* ac_ppid; void* ac_pid; int /*<<< orphan*/  ac_gid; int /*<<< orphan*/  ac_gid16; int /*<<< orphan*/  ac_uid; int /*<<< orphan*/  ac_uid16; } ;
typedef  TYPE_3__ acct_t ;
struct TYPE_14__ {int /*<<< orphan*/  user_ns; } ;
struct TYPE_13__ {TYPE_2__* signal; int /*<<< orphan*/  real_parent; } ;
struct TYPE_11__ {TYPE_1__* rlim; } ;
struct TYPE_10__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 size_t RLIMIT_FSIZE ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  __kernel_write (struct file*,TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_free_space (struct bsd_acct_struct*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  file_end_write (struct file*) ; 
 scalar_t__ file_start_write_trylock (struct file*) ; 
 int /*<<< orphan*/  fill_ac (TYPE_3__*) ; 
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cred* override_creds (TYPE_6__*) ; 
 TYPE_4__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 void* task_tgid_nr_ns (TYPE_4__*,struct pid_namespace*) ; 

__attribute__((used)) static void do_acct_process(struct bsd_acct_struct *acct)
{
	acct_t ac;
	unsigned long flim;
	const struct cred *orig_cred;
	struct file *file = acct->file;

	/*
	 * Accounting records are not subject to resource limits.
	 */
	flim = current->signal->rlim[RLIMIT_FSIZE].rlim_cur;
	current->signal->rlim[RLIMIT_FSIZE].rlim_cur = RLIM_INFINITY;
	/* Perform file operations on behalf of whoever enabled accounting */
	orig_cred = override_creds(file->f_cred);

	/*
	 * First check to see if there is enough free_space to continue
	 * the process accounting system.
	 */
	if (!check_free_space(acct))
		goto out;

	fill_ac(&ac);
	/* we really need to bite the bullet and change layout */
	ac.ac_uid = from_kuid_munged(file->f_cred->user_ns, orig_cred->uid);
	ac.ac_gid = from_kgid_munged(file->f_cred->user_ns, orig_cred->gid);
#if ACCT_VERSION == 1 || ACCT_VERSION == 2
	/* backward-compatible 16 bit fields */
	ac.ac_uid16 = ac.ac_uid;
	ac.ac_gid16 = ac.ac_gid;
#endif
#if ACCT_VERSION == 3
	{
		struct pid_namespace *ns = acct->ns;

		ac.ac_pid = task_tgid_nr_ns(current, ns);
		rcu_read_lock();
		ac.ac_ppid = task_tgid_nr_ns(rcu_dereference(current->real_parent),
					     ns);
		rcu_read_unlock();
	}
#endif
	/*
	 * Get freeze protection. If the fs is frozen, just skip the write
	 * as we could deadlock the system otherwise.
	 */
	if (file_start_write_trylock(file)) {
		/* it's been opened O_APPEND, so position is irrelevant */
		loff_t pos = 0;
		__kernel_write(file, &ac, sizeof(acct_t), &pos);
		file_end_write(file);
	}
out:
	current->signal->rlim[RLIMIT_FSIZE].rlim_cur = flim;
	revert_creds(orig_cred);
}