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
struct dlm_user_proc {int dummy; } ;
struct dlm_ls {int dummy; } ;
struct TYPE_2__ {int pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  dlm_lock_recovery (struct dlm_ls*) ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_unlock_recovery (struct dlm_ls*) ; 
 int /*<<< orphan*/  do_purge (struct dlm_ls*,int,int) ; 
 int /*<<< orphan*/  purge_proc_locks (struct dlm_ls*,struct dlm_user_proc*) ; 
 int send_purge (struct dlm_ls*,int,int) ; 

int dlm_user_purge(struct dlm_ls *ls, struct dlm_user_proc *proc,
		   int nodeid, int pid)
{
	int error = 0;

	if (nodeid && (nodeid != dlm_our_nodeid())) {
		error = send_purge(ls, nodeid, pid);
	} else {
		dlm_lock_recovery(ls);
		if (pid == current->pid)
			purge_proc_locks(ls, proc);
		else
			do_purge(ls, nodeid, pid);
		dlm_unlock_recovery(ls);
	}
	return error;
}