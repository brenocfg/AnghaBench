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
typedef  scalar_t__ umode_t ;
typedef  int /*<<< orphan*/  tid_t ;
struct posix_acl {int dummy; } ;
struct inode {scalar_t__ i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 int __jfs_set_acl (int /*<<< orphan*/ ,struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int posix_acl_update_mode (struct inode*,scalar_t__*,struct posix_acl**) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

int jfs_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int rc;
	tid_t tid;
	int update_mode = 0;
	umode_t mode = inode->i_mode;

	tid = txBegin(inode->i_sb, 0);
	mutex_lock(&JFS_IP(inode)->commit_mutex);
	if (type == ACL_TYPE_ACCESS && acl) {
		rc = posix_acl_update_mode(inode, &mode, &acl);
		if (rc)
			goto end_tx;
		if (mode != inode->i_mode)
			update_mode = 1;
	}
	rc = __jfs_set_acl(tid, inode, type, acl);
	if (!rc) {
		if (update_mode) {
			inode->i_mode = mode;
			inode->i_ctime = current_time(inode);
			mark_inode_dirty(inode);
		}
		rc = txCommit(tid, 1, &inode, 0);
	}
end_tx:
	txEnd(tid);
	mutex_unlock(&JFS_IP(inode)->commit_mutex);
	return rc;
}