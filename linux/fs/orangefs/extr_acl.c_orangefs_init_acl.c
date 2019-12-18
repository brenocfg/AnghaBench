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
typedef  scalar_t__ umode_t ;
struct posix_acl {int dummy; } ;
struct inode {scalar_t__ i_mode; int /*<<< orphan*/ * i_acl; int /*<<< orphan*/ * i_default_acl; } ;
struct iattr {int /*<<< orphan*/  ia_valid; scalar_t__ ia_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  ATTR_MODE ; 
 int __orangefs_set_acl (struct inode*,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __orangefs_setattr (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  memset (struct iattr*,int /*<<< orphan*/ ,int) ; 
 int posix_acl_create (struct inode*,scalar_t__*,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int orangefs_init_acl(struct inode *inode, struct inode *dir)
{
	struct posix_acl *default_acl, *acl;
	umode_t mode = inode->i_mode;
	struct iattr iattr;
	int error = 0;

	error = posix_acl_create(dir, &mode, &default_acl, &acl);
	if (error)
		return error;

	if (default_acl) {
		error = __orangefs_set_acl(inode, default_acl,
					   ACL_TYPE_DEFAULT);
		posix_acl_release(default_acl);
	} else {
		inode->i_default_acl = NULL;
	}

	if (acl) {
		if (!error)
			error = __orangefs_set_acl(inode, acl, ACL_TYPE_ACCESS);
		posix_acl_release(acl);
	} else {
		inode->i_acl = NULL;
	}

	/* If mode of the inode was changed, then do a forcible ->setattr */
	if (mode != inode->i_mode) {
		memset(&iattr, 0, sizeof iattr);
		inode->i_mode = mode;
		iattr.ia_mode = mode;
		iattr.ia_valid |= ATTR_MODE;
		__orangefs_setattr(inode, &iattr);
	}

	return error;
}