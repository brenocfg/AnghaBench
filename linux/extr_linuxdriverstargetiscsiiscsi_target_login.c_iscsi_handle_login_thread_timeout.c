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
struct timer_list {int dummy; } ;
struct iscsi_np {int np_login_timer_flags; int /*<<< orphan*/  np_thread_lock; scalar_t__ np_thread; int /*<<< orphan*/  np_sockaddr; } ;

/* Variables and functions */
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  SIGINT ; 
 struct iscsi_np* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct iscsi_np* np ; 
 int /*<<< orphan*/  np_login_timer ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsi_handle_login_thread_timeout(struct timer_list *t)
{
	struct iscsi_np *np = from_timer(np, t, np_login_timer);

	spin_lock_bh(&np->np_thread_lock);
	pr_err("iSCSI Login timeout on Network Portal %pISpc\n",
			&np->np_sockaddr);

	if (np->np_login_timer_flags & ISCSI_TF_STOP) {
		spin_unlock_bh(&np->np_thread_lock);
		return;
	}

	if (np->np_thread)
		send_sig(SIGINT, np->np_thread, 1);

	np->np_login_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&np->np_thread_lock);
}