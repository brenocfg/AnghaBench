#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_mode; scalar_t__ i_size; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; } ;
struct TYPE_3__ {int mode; scalar_t__ size; } ;
struct fuse_setattr_in {TYPE_1__ attr; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  valid; int /*<<< orphan*/  fh; } ;
struct fuse_inode {int /*<<< orphan*/  state; int /*<<< orphan*/  lock; } ;
struct fuse_file {int /*<<< orphan*/  fh; } ;
struct fuse_conn {int writeback_cache; scalar_t__ atomic_o_trunc; int /*<<< orphan*/  default_permissions; } ;
struct fuse_attr_out {TYPE_1__ attr; int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  valid; int /*<<< orphan*/  fh; } ;
struct file {struct fuse_file* private_data; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  outarg ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_4__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int ATTR_CTIME ; 
 int ATTR_FORCE ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_OPEN ; 
 int ATTR_SIZE ; 
 int ATTR_TIMES_SET ; 
 int ATTR_UID ; 
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  FATTR_FH ; 
 int /*<<< orphan*/  FATTR_LOCKOWNER ; 
 int /*<<< orphan*/  FUSE_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUSE_I_SIZE_UNSTABLE ; 
 int S_IFMT ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  attr_timeout (struct fuse_setattr_in*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  fuse_change_attributes_common (struct inode*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_lock_owner_id (struct fuse_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_release_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_set_nowrite (struct inode*) ; 
 int /*<<< orphan*/  fuse_setattr_fill (struct fuse_conn*,int /*<<< orphan*/ *,struct inode*,struct fuse_setattr_in*,struct fuse_setattr_in*) ; 
 int fuse_simple_request (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  iattr_to_fattr (struct fuse_conn*,struct iattr*,struct fuse_setattr_in*,int) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_setattr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 
 int write_inode_now (struct inode*,int) ; 

int fuse_do_setattr(struct dentry *dentry, struct iattr *attr,
		    struct file *file)
{
	struct inode *inode = d_inode(dentry);
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	FUSE_ARGS(args);
	struct fuse_setattr_in inarg;
	struct fuse_attr_out outarg;
	bool is_truncate = false;
	bool is_wb = fc->writeback_cache;
	loff_t oldsize;
	int err;
	bool trust_local_cmtime = is_wb && S_ISREG(inode->i_mode);

	if (!fc->default_permissions)
		attr->ia_valid |= ATTR_FORCE;

	err = setattr_prepare(dentry, attr);
	if (err)
		return err;

	if (attr->ia_valid & ATTR_OPEN) {
		/* This is coming from open(..., ... | O_TRUNC); */
		WARN_ON(!(attr->ia_valid & ATTR_SIZE));
		WARN_ON(attr->ia_size != 0);
		if (fc->atomic_o_trunc) {
			/*
			 * No need to send request to userspace, since actual
			 * truncation has already been done by OPEN.  But still
			 * need to truncate page cache.
			 */
			i_size_write(inode, 0);
			truncate_pagecache(inode, 0);
			return 0;
		}
		file = NULL;
	}

	if (attr->ia_valid & ATTR_SIZE) {
		if (WARN_ON(!S_ISREG(inode->i_mode)))
			return -EIO;
		is_truncate = true;
	}

	/* Flush dirty data/metadata before non-truncate SETATTR */
	if (is_wb && S_ISREG(inode->i_mode) &&
	    attr->ia_valid &
			(ATTR_MODE | ATTR_UID | ATTR_GID | ATTR_MTIME_SET |
			 ATTR_TIMES_SET)) {
		err = write_inode_now(inode, true);
		if (err)
			return err;

		fuse_set_nowrite(inode);
		fuse_release_nowrite(inode);
	}

	if (is_truncate) {
		fuse_set_nowrite(inode);
		set_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
		if (trust_local_cmtime && attr->ia_size != inode->i_size)
			attr->ia_valid |= ATTR_MTIME | ATTR_CTIME;
	}

	memset(&inarg, 0, sizeof(inarg));
	memset(&outarg, 0, sizeof(outarg));
	iattr_to_fattr(fc, attr, &inarg, trust_local_cmtime);
	if (file) {
		struct fuse_file *ff = file->private_data;
		inarg.valid |= FATTR_FH;
		inarg.fh = ff->fh;
	}
	if (attr->ia_valid & ATTR_SIZE) {
		/* For mandatory locking in truncate */
		inarg.valid |= FATTR_LOCKOWNER;
		inarg.lock_owner = fuse_lock_owner_id(fc, current->files);
	}
	fuse_setattr_fill(fc, &args, inode, &inarg, &outarg);
	err = fuse_simple_request(fc, &args);
	if (err) {
		if (err == -EINTR)
			fuse_invalidate_attr(inode);
		goto error;
	}

	if ((inode->i_mode ^ outarg.attr.mode) & S_IFMT) {
		make_bad_inode(inode);
		err = -EIO;
		goto error;
	}

	spin_lock(&fi->lock);
	/* the kernel maintains i_mtime locally */
	if (trust_local_cmtime) {
		if (attr->ia_valid & ATTR_MTIME)
			inode->i_mtime = attr->ia_mtime;
		if (attr->ia_valid & ATTR_CTIME)
			inode->i_ctime = attr->ia_ctime;
		/* FIXME: clear I_DIRTY_SYNC? */
	}

	fuse_change_attributes_common(inode, &outarg.attr,
				      attr_timeout(&outarg));
	oldsize = inode->i_size;
	/* see the comment in fuse_change_attributes() */
	if (!is_wb || is_truncate || !S_ISREG(inode->i_mode))
		i_size_write(inode, outarg.attr.size);

	if (is_truncate) {
		/* NOTE: this may release/reacquire fi->lock */
		__fuse_release_nowrite(inode);
	}
	spin_unlock(&fi->lock);

	/*
	 * Only call invalidate_inode_pages2() after removing
	 * FUSE_NOWRITE, otherwise fuse_launder_page() would deadlock.
	 */
	if ((is_truncate || !is_wb) &&
	    S_ISREG(inode->i_mode) && oldsize != outarg.attr.size) {
		truncate_pagecache(inode, outarg.attr.size);
		invalidate_inode_pages2(inode->i_mapping);
	}

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
	return 0;

error:
	if (is_truncate)
		fuse_release_nowrite(inode);

	clear_bit(FUSE_I_SIZE_UNSTABLE, &fi->state);
	return err;
}