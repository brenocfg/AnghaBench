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
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; scalar_t__ i_nlink; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct iattr {unsigned int ia_valid; scalar_t__ ia_size; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct ext4_sb_info {scalar_t__ s_bitmap_maxbytes; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ i_disksize; int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/  i_data_sem; int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 unsigned int const ATTR_GID ; 
 unsigned int const ATTR_MODE ; 
 int ATTR_SIZE ; 
 unsigned int const ATTR_TIMES_SET ; 
 unsigned int const ATTR_UID ; 
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 int /*<<< orphan*/  EXT4_HT_QUOTA ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int EXT4_MAXQUOTAS_DEL_BLOCKS (int /*<<< orphan*/ ) ; 
 int EXT4_MAXQUOTAS_INIT_BLOCKS (int /*<<< orphan*/ ) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_I_VERSION (struct inode*) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int dquot_initialize (struct inode*) ; 
 int dquot_transfer (struct inode*,struct iattr*) ; 
 int ext4_begin_ordered_truncate (struct inode*,scalar_t__) ; 
 int ext4_break_layouts (struct inode*) ; 
 int ext4_forced_shutdown (struct ext4_sb_info*) ; 
 scalar_t__ ext4_handle_valid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_orphan_add (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_wait_for_tail_page_commit (struct inode*) ; 
 int fscrypt_prepare_setattr (struct dentry*,struct iattr*) ; 
 int fsverity_prepare_setattr (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 scalar_t__ is_quota_modification (struct inode*,struct iattr*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pagecache_isize_extended (struct inode*,scalar_t__,scalar_t__) ; 
 int posix_acl_chmod (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	int error, rc = 0;
	int orphan = 0;
	const unsigned int ia_valid = attr->ia_valid;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	if (unlikely(IS_IMMUTABLE(inode)))
		return -EPERM;

	if (unlikely(IS_APPEND(inode) &&
		     (ia_valid & (ATTR_MODE | ATTR_UID |
				  ATTR_GID | ATTR_TIMES_SET))))
		return -EPERM;

	error = setattr_prepare(dentry, attr);
	if (error)
		return error;

	error = fscrypt_prepare_setattr(dentry, attr);
	if (error)
		return error;

	error = fsverity_prepare_setattr(dentry, attr);
	if (error)
		return error;

	if (is_quota_modification(inode, attr)) {
		error = dquot_initialize(inode);
		if (error)
			return error;
	}
	if ((ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, inode->i_uid)) ||
	    (ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, inode->i_gid))) {
		handle_t *handle;

		/* (user+group)*(old+new) structure, inode write (sb,
		 * inode block, ? - but truncate inode update has it) */
		handle = ext4_journal_start(inode, EXT4_HT_QUOTA,
			(EXT4_MAXQUOTAS_INIT_BLOCKS(inode->i_sb) +
			 EXT4_MAXQUOTAS_DEL_BLOCKS(inode->i_sb)) + 3);
		if (IS_ERR(handle)) {
			error = PTR_ERR(handle);
			goto err_out;
		}

		/* dquot_transfer() calls back ext4_get_inode_usage() which
		 * counts xattr inode references.
		 */
		down_read(&EXT4_I(inode)->xattr_sem);
		error = dquot_transfer(inode, attr);
		up_read(&EXT4_I(inode)->xattr_sem);

		if (error) {
			ext4_journal_stop(handle);
			return error;
		}
		/* Update corresponding info in inode so that everything is in
		 * one transaction */
		if (attr->ia_valid & ATTR_UID)
			inode->i_uid = attr->ia_uid;
		if (attr->ia_valid & ATTR_GID)
			inode->i_gid = attr->ia_gid;
		error = ext4_mark_inode_dirty(handle, inode);
		ext4_journal_stop(handle);
	}

	if (attr->ia_valid & ATTR_SIZE) {
		handle_t *handle;
		loff_t oldsize = inode->i_size;
		int shrink = (attr->ia_size < inode->i_size);

		if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) {
			struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

			if (attr->ia_size > sbi->s_bitmap_maxbytes)
				return -EFBIG;
		}
		if (!S_ISREG(inode->i_mode))
			return -EINVAL;

		if (IS_I_VERSION(inode) && attr->ia_size != inode->i_size)
			inode_inc_iversion(inode);

		if (shrink) {
			if (ext4_should_order_data(inode)) {
				error = ext4_begin_ordered_truncate(inode,
							    attr->ia_size);
				if (error)
					goto err_out;
			}
			/*
			 * Blocks are going to be removed from the inode. Wait
			 * for dio in flight.
			 */
			inode_dio_wait(inode);
		}

		down_write(&EXT4_I(inode)->i_mmap_sem);

		rc = ext4_break_layouts(inode);
		if (rc) {
			up_write(&EXT4_I(inode)->i_mmap_sem);
			return rc;
		}

		if (attr->ia_size != inode->i_size) {
			handle = ext4_journal_start(inode, EXT4_HT_INODE, 3);
			if (IS_ERR(handle)) {
				error = PTR_ERR(handle);
				goto out_mmap_sem;
			}
			if (ext4_handle_valid(handle) && shrink) {
				error = ext4_orphan_add(handle, inode);
				orphan = 1;
			}
			/*
			 * Update c/mtime on truncate up, ext4_truncate() will
			 * update c/mtime in shrink case below
			 */
			if (!shrink) {
				inode->i_mtime = current_time(inode);
				inode->i_ctime = inode->i_mtime;
			}
			down_write(&EXT4_I(inode)->i_data_sem);
			EXT4_I(inode)->i_disksize = attr->ia_size;
			rc = ext4_mark_inode_dirty(handle, inode);
			if (!error)
				error = rc;
			/*
			 * We have to update i_size under i_data_sem together
			 * with i_disksize to avoid races with writeback code
			 * running ext4_wb_update_i_disksize().
			 */
			if (!error)
				i_size_write(inode, attr->ia_size);
			up_write(&EXT4_I(inode)->i_data_sem);
			ext4_journal_stop(handle);
			if (error)
				goto out_mmap_sem;
			if (!shrink) {
				pagecache_isize_extended(inode, oldsize,
							 inode->i_size);
			} else if (ext4_should_journal_data(inode)) {
				ext4_wait_for_tail_page_commit(inode);
			}
		}

		/*
		 * Truncate pagecache after we've waited for commit
		 * in data=journal mode to make pages freeable.
		 */
		truncate_pagecache(inode, inode->i_size);
		/*
		 * Call ext4_truncate() even if i_size didn't change to
		 * truncate possible preallocated blocks.
		 */
		if (attr->ia_size <= oldsize) {
			rc = ext4_truncate(inode);
			if (rc)
				error = rc;
		}
out_mmap_sem:
		up_write(&EXT4_I(inode)->i_mmap_sem);
	}

	if (!error) {
		setattr_copy(inode, attr);
		mark_inode_dirty(inode);
	}

	/*
	 * If the call to ext4_truncate failed to get a transaction handle at
	 * all, we need to clean up the in-core orphan list manually.
	 */
	if (orphan && inode->i_nlink)
		ext4_orphan_del(NULL, inode);

	if (!error && (ia_valid & ATTR_MODE))
		rc = posix_acl_chmod(inode, inode->i_mode);

err_out:
	ext4_std_error(inode->i_sb, error);
	if (!error)
		error = rc;
	return error;
}