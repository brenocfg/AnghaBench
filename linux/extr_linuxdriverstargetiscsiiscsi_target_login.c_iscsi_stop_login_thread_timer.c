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
struct iscsi_np {int np_login_timer_flags; int /*<<< orphan*/  np_thread_lock; int /*<<< orphan*/  np_login_timer; } ;

/* Variables and functions */
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_stop_login_thread_timer(struct iscsi_np *np)
{
	spin_lock_bh(&np->np_thread_lock);
	if (!(np->np_login_timer_flags & ISCSI_TF_RUNNING)) {
		spin_unlock_bh(&np->np_thread_lock);
		return;
	}
	np->np_login_timer_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&np->np_thread_lock);

	del_timer_sync(&np->np_login_timer);

	spin_lock_bh(&np->np_thread_lock);
	np->np_login_timer_flags &= ~ISCSI_TF_RUNNING;
	spin_unlock_bh(&np->np_thread_lock);
}