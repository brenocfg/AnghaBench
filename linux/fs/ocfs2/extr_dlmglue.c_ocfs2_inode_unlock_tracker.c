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
struct ocfs2_lock_res {int dummy; } ;
struct ocfs2_lock_holder {int /*<<< orphan*/  oh_ex; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct ocfs2_lock_res ip_inode_lockres; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_remove_holder (struct ocfs2_lock_res*,struct ocfs2_lock_holder*) ; 

void ocfs2_inode_unlock_tracker(struct inode *inode,
				int ex,
				struct ocfs2_lock_holder *oh,
				int had_lock)
{
	struct ocfs2_lock_res *lockres;

	lockres = &OCFS2_I(inode)->ip_inode_lockres;
	/* had_lock means that the currect process already takes the cluster
	 * lock previously.
	 * If had_lock is 1, we have nothing to do here.
	 * If had_lock is 0, we will release the lock.
	 */
	if (!had_lock) {
		ocfs2_inode_unlock(inode, oh->oh_ex);
		ocfs2_remove_holder(lockres, oh);
	}
}