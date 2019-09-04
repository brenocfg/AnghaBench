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
struct user_namespace {int dummy; } ;
struct task_struct {struct nsproxy* nsproxy; int /*<<< orphan*/  fs; } ;
struct nsproxy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 unsigned long CLONE_NEWCGROUP ; 
 unsigned long CLONE_NEWIPC ; 
 unsigned long CLONE_NEWNET ; 
 unsigned long CLONE_NEWNS ; 
 unsigned long CLONE_NEWPID ; 
 unsigned long CLONE_NEWUTS ; 
 unsigned long CLONE_SYSVSEM ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct nsproxy*) ; 
 int PTR_ERR (struct nsproxy*) ; 
 struct nsproxy* create_new_namespaces (unsigned long,struct task_struct*,struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nsproxy (struct nsproxy*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 struct user_namespace* task_cred_xxx (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct user_namespace* user_ns ; 

int copy_namespaces(unsigned long flags, struct task_struct *tsk)
{
	struct nsproxy *old_ns = tsk->nsproxy;
	struct user_namespace *user_ns = task_cred_xxx(tsk, user_ns);
	struct nsproxy *new_ns;

	if (likely(!(flags & (CLONE_NEWNS | CLONE_NEWUTS | CLONE_NEWIPC |
			      CLONE_NEWPID | CLONE_NEWNET |
			      CLONE_NEWCGROUP)))) {
		get_nsproxy(old_ns);
		return 0;
	}

	if (!ns_capable(user_ns, CAP_SYS_ADMIN))
		return -EPERM;

	/*
	 * CLONE_NEWIPC must detach from the undolist: after switching
	 * to a new ipc namespace, the semaphore arrays from the old
	 * namespace are unreachable.  In clone parlance, CLONE_SYSVSEM
	 * means share undolist with parent, so we must forbid using
	 * it along with CLONE_NEWIPC.
	 */
	if ((flags & (CLONE_NEWIPC | CLONE_SYSVSEM)) ==
		(CLONE_NEWIPC | CLONE_SYSVSEM)) 
		return -EINVAL;

	new_ns = create_new_namespaces(flags, tsk, user_ns, tsk->fs);
	if (IS_ERR(new_ns))
		return  PTR_ERR(new_ns);

	tsk->nsproxy = new_ns;
	return 0;
}