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
struct iscsi_np {int enabled; TYPE_1__* np_transport; int /*<<< orphan*/  np_sockaddr; int /*<<< orphan*/  np_list; int /*<<< orphan*/ * np_thread; int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  np_thread_state; scalar_t__ np_exports; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  (* iscsit_free_np ) (struct iscsi_np*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_NP_THREAD_SHUTDOWN ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  iscsit_put_transport (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct iscsi_np*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  np_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_np*) ; 

int iscsit_del_np(struct iscsi_np *np)
{
	spin_lock_bh(&np->np_thread_lock);
	np->np_exports--;
	if (np->np_exports) {
		np->enabled = true;
		spin_unlock_bh(&np->np_thread_lock);
		return 0;
	}
	np->np_thread_state = ISCSI_NP_THREAD_SHUTDOWN;
	spin_unlock_bh(&np->np_thread_lock);

	if (np->np_thread) {
		/*
		 * We need to send the signal to wakeup Linux/Net
		 * which may be sleeping in sock_accept()..
		 */
		send_sig(SIGINT, np->np_thread, 1);
		kthread_stop(np->np_thread);
		np->np_thread = NULL;
	}

	np->np_transport->iscsit_free_np(np);

	mutex_lock(&np_lock);
	list_del(&np->np_list);
	mutex_unlock(&np_lock);

	pr_debug("CORE[0] - Removed Network Portal: %pISpc on %s\n",
		&np->np_sockaddr, np->np_transport->name);

	iscsit_put_transport(np->np_transport);
	kfree(np);
	return 0;
}