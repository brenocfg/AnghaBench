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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/ * i_acl; int /*<<< orphan*/ * i_default_acl; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_TYPE_DEFAULT ; 
 int __f2fs_set_acl (struct inode*,int /*<<< orphan*/ ,struct posix_acl*,struct page*) ; 
 int f2fs_acl_create (struct inode*,int /*<<< orphan*/ *,struct posix_acl**,struct posix_acl**,struct page*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

int f2fs_init_acl(struct inode *inode, struct inode *dir, struct page *ipage,
							struct page *dpage)
{
	struct posix_acl *default_acl = NULL, *acl = NULL;
	int error = 0;

	error = f2fs_acl_create(dir, &inode->i_mode, &default_acl, &acl, dpage);
	if (error)
		return error;

	f2fs_mark_inode_dirty_sync(inode, true);

	if (default_acl) {
		error = __f2fs_set_acl(inode, ACL_TYPE_DEFAULT, default_acl,
				       ipage);
		posix_acl_release(default_acl);
	} else {
		inode->i_default_acl = NULL;
	}
	if (acl) {
		if (!error)
			error = __f2fs_set_acl(inode, ACL_TYPE_ACCESS, acl,
					       ipage);
		posix_acl_release(acl);
	} else {
		inode->i_acl = NULL;
	}

	return error;
}