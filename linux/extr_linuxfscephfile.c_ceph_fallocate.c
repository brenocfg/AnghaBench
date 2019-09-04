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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {struct ceph_file_info* private_data; } ;
struct ceph_inode_info {scalar_t__ i_inline_version; int /*<<< orphan*/  i_ceph_lock; } ;
struct ceph_fs_client {TYPE_1__* client; int /*<<< orphan*/  max_file_size; } ;
struct ceph_file_info {int fmode; } ;
struct ceph_cap_flush {int dummy; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  osdc; } ;

/* Variables and functions */
 int CEPH_CAP_FILE_BUFFER ; 
 int CEPH_CAP_FILE_LAZYIO ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_WR ; 
 int CEPH_FILE_MODE_LAZY ; 
 scalar_t__ CEPH_INLINE_NONE ; 
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  CEPH_OSDMAP_FULL ; 
 int /*<<< orphan*/  CHECK_CAPS_AUTHONLY ; 
 int /*<<< orphan*/  CHECK_CAPS_NODELAY ; 
 int EDQUOT ; 
 long EFBIG ; 
 long ENOMEM ; 
 int ENOSPC ; 
 long EOPNOTSUPP ; 
 int EROFS ; 
 int FALLOC_FL_KEEP_SIZE ; 
 int FALLOC_FL_PUNCH_HOLE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int __ceph_mark_dirty_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,struct ceph_cap_flush**) ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int) ; 
 struct ceph_cap_flush* ceph_alloc_cap_flush () ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_free_cap_flush (struct ceph_cap_flush*) ; 
 int ceph_get_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int,scalar_t__,int*,int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 scalar_t__ ceph_inode_set_size (struct inode*,scalar_t__) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 scalar_t__ ceph_osdmap_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_put_cap_refs (struct ceph_inode_info*,int) ; 
 scalar_t__ ceph_quota_is_max_bytes_approaching (struct inode*,scalar_t__) ; 
 scalar_t__ ceph_quota_is_max_bytes_exceeded (struct inode*,scalar_t__) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int ceph_uninline_data (struct file*,int /*<<< orphan*/ *) ; 
 int ceph_zero_objects (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ceph_zero_pagecache_range (struct inode*,scalar_t__,scalar_t__) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache_range (struct inode*,scalar_t__,int) ; 

__attribute__((used)) static long ceph_fallocate(struct file *file, int mode,
				loff_t offset, loff_t length)
{
	struct ceph_file_info *fi = file->private_data;
	struct inode *inode = file_inode(file);
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_cap_flush *prealloc_cf;
	int want, got = 0;
	int dirty;
	int ret = 0;
	loff_t endoff = 0;
	loff_t size;

	if ((offset + length) > max(i_size_read(inode), fsc->max_file_size))
		return -EFBIG;

	if (mode & ~(FALLOC_FL_KEEP_SIZE | FALLOC_FL_PUNCH_HOLE))
		return -EOPNOTSUPP;

	if (!S_ISREG(inode->i_mode))
		return -EOPNOTSUPP;

	prealloc_cf = ceph_alloc_cap_flush();
	if (!prealloc_cf)
		return -ENOMEM;

	inode_lock(inode);

	if (ceph_snap(inode) != CEPH_NOSNAP) {
		ret = -EROFS;
		goto unlock;
	}

	if (!(mode & (FALLOC_FL_PUNCH_HOLE | FALLOC_FL_KEEP_SIZE)) &&
	    ceph_quota_is_max_bytes_exceeded(inode, offset + length)) {
		ret = -EDQUOT;
		goto unlock;
	}

	if (ceph_osdmap_flag(&fsc->client->osdc, CEPH_OSDMAP_FULL) &&
	    !(mode & FALLOC_FL_PUNCH_HOLE)) {
		ret = -ENOSPC;
		goto unlock;
	}

	if (ci->i_inline_version != CEPH_INLINE_NONE) {
		ret = ceph_uninline_data(file, NULL);
		if (ret < 0)
			goto unlock;
	}

	size = i_size_read(inode);
	if (!(mode & FALLOC_FL_KEEP_SIZE)) {
		endoff = offset + length;
		ret = inode_newsize_ok(inode, endoff);
		if (ret)
			goto unlock;
	}

	if (fi->fmode & CEPH_FILE_MODE_LAZY)
		want = CEPH_CAP_FILE_BUFFER | CEPH_CAP_FILE_LAZYIO;
	else
		want = CEPH_CAP_FILE_BUFFER;

	ret = ceph_get_caps(ci, CEPH_CAP_FILE_WR, want, endoff, &got, NULL);
	if (ret < 0)
		goto unlock;

	if (mode & FALLOC_FL_PUNCH_HOLE) {
		if (offset < size)
			ceph_zero_pagecache_range(inode, offset, length);
		ret = ceph_zero_objects(inode, offset, length);
	} else if (endoff > size) {
		truncate_pagecache_range(inode, size, -1);
		if (ceph_inode_set_size(inode, endoff))
			ceph_check_caps(ceph_inode(inode),
				CHECK_CAPS_AUTHONLY, NULL);
	}

	if (!ret) {
		spin_lock(&ci->i_ceph_lock);
		ci->i_inline_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_FILE_WR,
					       &prealloc_cf);
		spin_unlock(&ci->i_ceph_lock);
		if (dirty)
			__mark_inode_dirty(inode, dirty);
		if ((endoff > size) &&
		    ceph_quota_is_max_bytes_approaching(inode, endoff))
			ceph_check_caps(ci, CHECK_CAPS_NODELAY, NULL);
	}

	ceph_put_cap_refs(ci, got);
unlock:
	inode_unlock(inode);
	ceph_free_cap_flush(prealloc_cf);
	return ret;
}