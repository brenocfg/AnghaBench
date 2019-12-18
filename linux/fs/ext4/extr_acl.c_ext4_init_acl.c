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
struct inode {int /*<<< orphan*/ * i_acl; int /*<<< orphan*/ * i_default_acl; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  XATTR_CREATE ; 
 int __ext4_set_acl (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int posix_acl_create (struct inode*,int /*<<< orphan*/ *,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int
ext4_init_acl(handle_t *handle, struct inode *inode, struct inode *dir)
{
	struct posix_acl *default_acl, *acl;
	int error;

	error = posix_acl_create(dir, &inode->i_mode, &default_acl, &acl);
	if (error)
		return error;

	if (default_acl) {
		error = __ext4_set_acl(handle, inode, ACL_TYPE_DEFAULT,
				       default_acl, XATTR_CREATE);
		posix_acl_release(default_acl);
	} else {
		inode->i_default_acl = NULL;
	}
	if (acl) {
		if (!error)
			error = __ext4_set_acl(handle, inode, ACL_TYPE_ACCESS,
					       acl, XATTR_CREATE);
		posix_acl_release(acl);
	} else {
		inode->i_acl = NULL;
	}
	return error;
}