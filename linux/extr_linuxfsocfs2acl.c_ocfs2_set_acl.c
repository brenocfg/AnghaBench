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
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EACCES ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (void*) ; 
 int OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS ; 
 int OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT ; 
 scalar_t__ PTR_ERR (void*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* ocfs2_acl_to_xattr (struct posix_acl*,size_t*) ; 
 int ocfs2_xattr_set (struct inode*,int,char*,void*,size_t,int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_set_handle (int /*<<< orphan*/ *,struct inode*,struct buffer_head*,int,char*,void*,size_t,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*) ; 

__attribute__((used)) static int ocfs2_set_acl(handle_t *handle,
			 struct inode *inode,
			 struct buffer_head *di_bh,
			 int type,
			 struct posix_acl *acl,
			 struct ocfs2_alloc_context *meta_ac,
			 struct ocfs2_alloc_context *data_ac)
{
	int name_index;
	void *value = NULL;
	size_t size = 0;
	int ret;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

	switch (type) {
	case ACL_TYPE_ACCESS:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_ACCESS;
		break;
	case ACL_TYPE_DEFAULT:
		name_index = OCFS2_XATTR_INDEX_POSIX_ACL_DEFAULT;
		if (!S_ISDIR(inode->i_mode))
			return acl ? -EACCES : 0;
		break;
	default:
		return -EINVAL;
	}

	if (acl) {
		value = ocfs2_acl_to_xattr(acl, &size);
		if (IS_ERR(value))
			return (int)PTR_ERR(value);
	}

	if (handle)
		ret = ocfs2_xattr_set_handle(handle, inode, di_bh, name_index,
					     "", value, size, 0,
					     meta_ac, data_ac);
	else
		ret = ocfs2_xattr_set(inode, name_index, "", value, size, 0);

	kfree(value);

	return ret;
}