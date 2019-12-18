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
typedef  scalar_t__ u64 ;
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; struct timespec64 i_mtime; } ;
struct fuse_inode {scalar_t__ attr_version; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct fuse_conn {int writeback_cache; scalar_t__ auto_inval_data; int /*<<< orphan*/  explicit_inval_data; } ;
struct fuse_attr {scalar_t__ size; int /*<<< orphan*/  mtimensec; int /*<<< orphan*/  mtime; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_I_SIZE_UNSTABLE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_change_attributes_common (struct inode*,struct fuse_attr*,scalar_t__) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespec64_equal (struct timespec64*,struct timespec64*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 

void fuse_change_attributes(struct inode *inode, struct fuse_attr *attr,
			    u64 attr_valid, u64 attr_version)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_inode *fi = get_fuse_inode(inode);
	bool is_wb = fc->writeback_cache;
	loff_t oldsize;
	struct timespec64 old_mtime;

	spin_lock(&fi->lock);
	if ((attr_version != 0 && fi->attr_version > attr_version) ||
	    test_bit(FUSE_I_SIZE_UNSTABLE, &fi->state)) {
		spin_unlock(&fi->lock);
		return;
	}

	old_mtime = inode->i_mtime;
	fuse_change_attributes_common(inode, attr, attr_valid);

	oldsize = inode->i_size;
	/*
	 * In case of writeback_cache enabled, the cached writes beyond EOF
	 * extend local i_size without keeping userspace server in sync. So,
	 * attr->size coming from server can be stale. We cannot trust it.
	 */
	if (!is_wb || !S_ISREG(inode->i_mode))
		i_size_write(inode, attr->size);
	spin_unlock(&fi->lock);

	if (!is_wb && S_ISREG(inode->i_mode)) {
		bool inval = false;

		if (oldsize != attr->size) {
			truncate_pagecache(inode, attr->size);
			if (!fc->explicit_inval_data)
				inval = true;
		} else if (fc->auto_inval_data) {
			struct timespec64 new_mtime = {
				.tv_sec = attr->mtime,
				.tv_nsec = attr->mtimensec,
			};

			/*
			 * Auto inval mode also checks and invalidates if mtime
			 * has changed.
			 */
			if (!timespec64_equal(&old_mtime, &new_mtime))
				inval = true;
		}

		if (inval)
			invalidate_inode_pages2(inode->i_mapping);
	}
}