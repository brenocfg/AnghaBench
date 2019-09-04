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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EACCES ; 
 int EINVAL ; 
 int EXT2_XATTR_INDEX_POSIX_ACL_ACCESS ; 
 int EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ PTR_ERR (void*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 void* ext2_acl_to_disk (struct posix_acl*,size_t*) ; 
 int ext2_xattr_set (struct inode*,int,char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int
__ext2_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	int name_index;
	void *value = NULL;
	size_t size = 0;
	int error;

	switch(type) {
		case ACL_TYPE_ACCESS:
			name_index = EXT2_XATTR_INDEX_POSIX_ACL_ACCESS;
			break;

		case ACL_TYPE_DEFAULT:
			name_index = EXT2_XATTR_INDEX_POSIX_ACL_DEFAULT;
			if (!S_ISDIR(inode->i_mode))
				return acl ? -EACCES : 0;
			break;

		default:
			return -EINVAL;
	}
 	if (acl) {
		value = ext2_acl_to_disk(acl, &size);
		if (IS_ERR(value))
			return (int)PTR_ERR(value);
	}

	error = ext2_xattr_set(inode, name_index, "", value, size, 0);

	kfree(value);
	if (!error)
		set_cached_acl(inode, type, acl);
	return error;
}