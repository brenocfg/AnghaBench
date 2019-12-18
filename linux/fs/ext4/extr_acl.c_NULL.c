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
struct posix_acl {int /*<<< orphan*/  a_count; } ;
struct inode {scalar_t__ i_mode; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_XATTR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ext4_set_acl (int /*<<< orphan*/ *,struct inode*,int,struct posix_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 size_t ext4_acl_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int ext4_xattr_set_credits (struct inode*,size_t,int,int*) ; 
 int posix_acl_update_mode (struct inode*,scalar_t__*,struct posix_acl**) ; 

int
ext4_set_acl(struct inode *inode, struct posix_acl *acl, int type)
{
	handle_t *handle;
	int error, credits, retries = 0;
	size_t acl_size = acl ? ext4_acl_size(acl->a_count) : 0;
	umode_t mode = inode->i_mode;
	int update_mode = 0;

	error = dquot_initialize(inode);
	if (error)
		return error;
retry:
	error = ext4_xattr_set_credits(inode, acl_size, false /* is_create */,
				       &credits);
	if (error)
		return error;

	handle = ext4_journal_start(inode, EXT4_HT_XATTR, credits);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if ((type == ACL_TYPE_ACCESS) && acl) {
		error = posix_acl_update_mode(inode, &mode, &acl);
		if (error)
			goto out_stop;
		if (mode != inode->i_mode)
			update_mode = 1;
	}

	error = __ext4_set_acl(handle, inode, type, acl, 0 /* xattr_flags */);
	if (!error && update_mode) {
		inode->i_mode = mode;
		inode->i_ctime = current_time(inode);
		ext4_mark_inode_dirty(handle, inode);
	}
out_stop:
	ext4_journal_stop(handle);
	if (error == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		goto retry;
	return error;
}