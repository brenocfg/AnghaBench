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
typedef  int /*<<< orphan*/  tid_t ;
struct posix_acl {int dummy; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_acl; int /*<<< orphan*/ * i_default_acl; } ;
struct TYPE_2__ {int mode2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 TYPE_1__* JFS_IP (struct inode*) ; 
 int __jfs_set_acl (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,struct posix_acl*) ; 
 int posix_acl_create (struct inode*,int*,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int jfs_init_acl(tid_t tid, struct inode *inode, struct inode *dir)
{
	struct posix_acl *default_acl, *acl;
	int rc = 0;

	rc = posix_acl_create(dir, &inode->i_mode, &default_acl, &acl);
	if (rc)
		return rc;

	if (default_acl) {
		rc = __jfs_set_acl(tid, inode, ACL_TYPE_DEFAULT, default_acl);
		posix_acl_release(default_acl);
	} else {
		inode->i_default_acl = NULL;
	}

	if (acl) {
		if (!rc)
			rc = __jfs_set_acl(tid, inode, ACL_TYPE_ACCESS, acl);
		posix_acl_release(acl);
	} else {
		inode->i_acl = NULL;
	}

	JFS_IP(inode)->mode2 = (JFS_IP(inode)->mode2 & 0xffff0000) |
			       inode->i_mode;

	return rc;
}