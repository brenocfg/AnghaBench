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
struct iomap {scalar_t__ offset; scalar_t__ length; } ;
struct inode {int i_blkbits; scalar_t__ i_nlink; int /*<<< orphan*/  i_size; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_orphan; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 unsigned int IOMAP_FAULT ; 
 unsigned int IOMAP_WRITE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_can_truncate (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_truncate_failed_write (struct inode*) ; 
 scalar_t__ ext4_update_inode_size (struct inode*,int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_iomap_end(struct inode *inode, loff_t offset, loff_t length,
			  ssize_t written, unsigned flags, struct iomap *iomap)
{
	int ret = 0;
	handle_t *handle;
	int blkbits = inode->i_blkbits;
	bool truncate = false;

	if (!(flags & IOMAP_WRITE) || (flags & IOMAP_FAULT))
		return 0;

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		goto orphan_del;
	}
	if (ext4_update_inode_size(inode, offset + written))
		ext4_mark_inode_dirty(handle, inode);
	/*
	 * We may need to truncate allocated but not written blocks beyond EOF.
	 */
	if (iomap->offset + iomap->length > 
	    ALIGN(inode->i_size, 1 << blkbits)) {
		ext4_lblk_t written_blk, end_blk;

		written_blk = (offset + written) >> blkbits;
		end_blk = (offset + length) >> blkbits;
		if (written_blk < end_blk && ext4_can_truncate(inode))
			truncate = true;
	}
	/*
	 * Remove inode from orphan list if we were extending a inode and
	 * everything went fine.
	 */
	if (!truncate && inode->i_nlink &&
	    !list_empty(&EXT4_I(inode)->i_orphan))
		ext4_orphan_del(handle, inode);
	ext4_journal_stop(handle);
	if (truncate) {
		ext4_truncate_failed_write(inode);
orphan_del:
		/*
		 * If truncate failed early the inode might still be on the
		 * orphan list; we need to make sure the inode is removed from
		 * the orphan list in that case.
		 */
		if (inode->i_nlink)
			ext4_orphan_del(NULL, inode);
	}
	return ret;
}