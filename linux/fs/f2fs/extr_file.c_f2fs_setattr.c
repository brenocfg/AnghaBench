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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_acl_mode; int /*<<< orphan*/  i_sem; void* last_disk_size; int /*<<< orphan*/ * i_gc_rwsem; int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int EIO ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_ACL_MODE ; 
 scalar_t__ MAX_INLINE_DATA (struct inode*) ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_REPAIR ; 
 size_t WRITE ; 
 int /*<<< orphan*/  __setattr_copy (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int dquot_initialize (struct inode*) ; 
 int dquot_transfer (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  f2fs_balance_fs (int /*<<< orphan*/ ,int) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_get_inode_mode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_lock_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int f2fs_truncate (struct inode*) ; 
 int /*<<< orphan*/  f2fs_unlock_op (int /*<<< orphan*/ ) ; 
 int fscrypt_prepare_setattr (struct dentry*,struct iattr*) ; 
 int fsverity_prepare_setattr (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* i_size_read (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_quota_modification (struct inode*,struct iattr*) ; 
 int posix_acl_chmod (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int f2fs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	int err;

	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		return -EIO;

	err = setattr_prepare(dentry, attr);
	if (err)
		return err;

	err = fscrypt_prepare_setattr(dentry, attr);
	if (err)
		return err;

	err = fsverity_prepare_setattr(dentry, attr);
	if (err)
		return err;

	if (is_quota_modification(inode, attr)) {
		err = dquot_initialize(inode);
		if (err)
			return err;
	}
	if ((attr->ia_valid & ATTR_UID &&
		!uid_eq(attr->ia_uid, inode->i_uid)) ||
		(attr->ia_valid & ATTR_GID &&
		!gid_eq(attr->ia_gid, inode->i_gid))) {
		f2fs_lock_op(F2FS_I_SB(inode));
		err = dquot_transfer(inode, attr);
		if (err) {
			set_sbi_flag(F2FS_I_SB(inode),
					SBI_QUOTA_NEED_REPAIR);
			f2fs_unlock_op(F2FS_I_SB(inode));
			return err;
		}
		/*
		 * update uid/gid under lock_op(), so that dquot and inode can
		 * be updated atomically.
		 */
		if (attr->ia_valid & ATTR_UID)
			inode->i_uid = attr->ia_uid;
		if (attr->ia_valid & ATTR_GID)
			inode->i_gid = attr->ia_gid;
		f2fs_mark_inode_dirty_sync(inode, true);
		f2fs_unlock_op(F2FS_I_SB(inode));
	}

	if (attr->ia_valid & ATTR_SIZE) {
		loff_t old_size = i_size_read(inode);

		if (attr->ia_size > MAX_INLINE_DATA(inode)) {
			/*
			 * should convert inline inode before i_size_write to
			 * keep smaller than inline_data size with inline flag.
			 */
			err = f2fs_convert_inline_inode(inode);
			if (err)
				return err;
		}

		down_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		down_write(&F2FS_I(inode)->i_mmap_sem);

		truncate_setsize(inode, attr->ia_size);

		if (attr->ia_size <= old_size)
			err = f2fs_truncate(inode);
		/*
		 * do not trim all blocks after i_size if target size is
		 * larger than i_size.
		 */
		up_write(&F2FS_I(inode)->i_mmap_sem);
		up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		if (err)
			return err;

		down_write(&F2FS_I(inode)->i_sem);
		inode->i_mtime = inode->i_ctime = current_time(inode);
		F2FS_I(inode)->last_disk_size = i_size_read(inode);
		up_write(&F2FS_I(inode)->i_sem);
	}

	__setattr_copy(inode, attr);

	if (attr->ia_valid & ATTR_MODE) {
		err = posix_acl_chmod(inode, f2fs_get_inode_mode(inode));
		if (err || is_inode_flag_set(inode, FI_ACL_MODE)) {
			inode->i_mode = F2FS_I(inode)->i_acl_mode;
			clear_inode_flag(inode, FI_ACL_MODE);
		}
	}

	/* file size may changed here */
	f2fs_mark_inode_dirty_sync(inode, true);

	/* inode change will produce dirty node pages flushed by checkpoint */
	f2fs_balance_fs(F2FS_I_SB(inode), true);

	return err;
}