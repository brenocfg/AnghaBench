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
typedef  int /*<<< orphan*/  umode_t ;
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int __ext2_set_acl (struct inode*,struct posix_acl*,int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int posix_acl_update_mode (struct inode*,int /*<<< orphan*/ *,struct posix_acl**) ; 

int
ext2_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int error;
	int update_mode = 0;
	umode_t mode = inode->i_mode;

	if (type == ACL_TYPE_ACCESS && acl) {
		error = posix_acl_update_mode(inode, &mode, &acl);
		if (error)
			return error;
		update_mode = 1;
	}
	error = __ext2_set_acl(inode, acl, type);
	if (!error && update_mode) {
		inode->i_mode = mode;
		inode->i_ctime = current_time(inode);
		mark_inode_dirty(inode);
	}
	return error;
}