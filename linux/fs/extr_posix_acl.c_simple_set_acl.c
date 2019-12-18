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
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int posix_acl_update_mode (struct inode*,int /*<<< orphan*/ *,struct posix_acl**) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

int simple_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int error;

	if (type == ACL_TYPE_ACCESS) {
		error = posix_acl_update_mode(inode,
				&inode->i_mode, &acl);
		if (error)
			return error;
	}

	inode->i_ctime = current_time(inode);
	set_cached_acl(inode, type, acl);
	return 0;
}