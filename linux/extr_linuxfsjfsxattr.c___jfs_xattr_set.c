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
typedef  int /*<<< orphan*/  tid_t ;
struct jfs_inode_info {int /*<<< orphan*/  commit_mutex; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int __jfs_setxattr (int /*<<< orphan*/ ,struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __jfs_xattr_set(struct inode *inode, const char *name,
			   const void *value, size_t size, int flags)
{
	struct jfs_inode_info *ji = JFS_IP(inode);
	tid_t tid;
	int rc;

	tid = txBegin(inode->i_sb, 0);
	mutex_lock(&ji->commit_mutex);
	rc = __jfs_setxattr(tid, inode, name, value, size, flags);
	if (!rc)
		rc = txCommit(tid, 1, &inode, 0);
	txEnd(tid);
	mutex_unlock(&ji->commit_mutex);

	return rc;
}