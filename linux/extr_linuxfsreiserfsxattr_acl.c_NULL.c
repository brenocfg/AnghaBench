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
struct inode {int dummy; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  BUG () ; 
 int ENODATA ; 
 int ENOMEM ; 
 int ENOSYS ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 char* XATTR_NAME_POSIX_ACL_ACCESS ; 
 char* XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct posix_acl* reiserfs_posix_acl_from_disk (char*,int) ; 
 int reiserfs_xattr_get (struct inode*,char*,char*,int) ; 

struct posix_acl *reiserfs_get_acl(struct inode *inode, int type)
{
	char *name, *value;
	struct posix_acl *acl;
	int size;
	int retval;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name = XATTR_NAME_POSIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		name = XATTR_NAME_POSIX_ACL_DEFAULT;
		break;
	default:
		BUG();
	}

	size = reiserfs_xattr_get(inode, name, NULL, 0);
	if (size < 0) {
		if (size == -ENODATA || size == -ENOSYS)
			return NULL;
		return ERR_PTR(size);
	}

	value = kmalloc(size, GFP_NOFS);
	if (!value)
		return ERR_PTR(-ENOMEM);

	retval = reiserfs_xattr_get(inode, name, value, size);
	if (retval == -ENODATA || retval == -ENOSYS) {
		/*
		 * This shouldn't actually happen as it should have
		 * been caught above.. but just in case
		 */
		acl = NULL;
	} else if (retval < 0) {
		acl = ERR_PTR(retval);
	} else {
		acl = reiserfs_posix_acl_from_disk(value, retval);
	}

	kfree(value);
	return acl;
}