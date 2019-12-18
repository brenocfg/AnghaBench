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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct hfsplus_inode_info {int extent_state; int /*<<< orphan*/  flags; int /*<<< orphan*/  cached_extents; int /*<<< orphan*/  cached_start; int /*<<< orphan*/  extents_lock; } ;
struct hfs_find_data {int /*<<< orphan*/  entrylength; int /*<<< orphan*/  entryoffset; int /*<<< orphan*/  bnode; TYPE_1__* tree; int /*<<< orphan*/  search_key; } ;
typedef  int /*<<< orphan*/  hfsplus_extent_rec ;
struct TYPE_2__ {scalar_t__ depth; } ;

/* Variables and functions */
 int ENOENT ; 
 int HFSPLUS_EXT_DIRTY ; 
 int HFSPLUS_EXT_NEW ; 
 struct hfsplus_inode_info* HFSPLUS_I (struct inode*) ; 
 scalar_t__ HFSPLUS_IS_RSRC (struct inode*) ; 
 int /*<<< orphan*/  HFSPLUS_I_EXT_DIRTY ; 
 int /*<<< orphan*/  HFSPLUS_TYPE_DATA ; 
 int /*<<< orphan*/  HFSPLUS_TYPE_RSRC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int hfs_bmap_reserve (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  hfs_bnode_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hfs_brec_find (struct hfs_find_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_brec_insert (struct hfs_find_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hfs_find_rec_by_key ; 
 int /*<<< orphan*/  hfsplus_ext_build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __hfsplus_ext_write_extent(struct inode *inode,
		struct hfs_find_data *fd)
{
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	int res;

	WARN_ON(!mutex_is_locked(&hip->extents_lock));

	hfsplus_ext_build_key(fd->search_key, inode->i_ino, hip->cached_start,
			      HFSPLUS_IS_RSRC(inode) ?
				HFSPLUS_TYPE_RSRC : HFSPLUS_TYPE_DATA);

	res = hfs_brec_find(fd, hfs_find_rec_by_key);
	if (hip->extent_state & HFSPLUS_EXT_NEW) {
		if (res != -ENOENT)
			return res;
		/* Fail early and avoid ENOSPC during the btree operation */
		res = hfs_bmap_reserve(fd->tree, fd->tree->depth + 1);
		if (res)
			return res;
		hfs_brec_insert(fd, hip->cached_extents,
				sizeof(hfsplus_extent_rec));
		hip->extent_state &= ~(HFSPLUS_EXT_DIRTY | HFSPLUS_EXT_NEW);
	} else {
		if (res)
			return res;
		hfs_bnode_write(fd->bnode, hip->cached_extents,
				fd->entryoffset, fd->entrylength);
		hip->extent_state &= ~HFSPLUS_EXT_DIRTY;
	}

	/*
	 * We can't just use hfsplus_mark_inode_dirty here, because we
	 * also get called from hfsplus_write_inode, which should not
	 * redirty the inode.  Instead the callers have to be careful
	 * to explicily mark the inode dirty, too.
	 */
	set_bit(HFSPLUS_I_EXT_DIRTY, &hip->flags);

	return 0;
}