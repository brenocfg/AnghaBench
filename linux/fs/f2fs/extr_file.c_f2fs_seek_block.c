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
struct inode {int /*<<< orphan*/  i_mapping; TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct dnode_of_data {scalar_t__ ofs_in_node; int /*<<< orphan*/  node_page; int /*<<< orphan*/  inode; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int s_maxbytes; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ ADDRS_PER_PAGE (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  DATA_GENERIC_ENHANCE ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 int PAGE_SHIFT ; 
 int SEEK_DATA ; 
 int SEEK_HOLE ; 
 scalar_t__ __found_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ __get_first_dirty_index (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ __is_valid_data_blkaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datablock_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_get_next_page_offset (struct dnode_of_data*,scalar_t__) ; 
 scalar_t__ f2fs_has_inline_data (struct inode*) ; 
 scalar_t__ f2fs_has_inline_dentry (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vfs_setpos (struct file*,int,int) ; 

__attribute__((used)) static loff_t f2fs_seek_block(struct file *file, loff_t offset, int whence)
{
	struct inode *inode = file->f_mapping->host;
	loff_t maxbytes = inode->i_sb->s_maxbytes;
	struct dnode_of_data dn;
	pgoff_t pgofs, end_offset, dirty;
	loff_t data_ofs = offset;
	loff_t isize;
	int err = 0;

	inode_lock(inode);

	isize = i_size_read(inode);
	if (offset >= isize)
		goto fail;

	/* handle inline data case */
	if (f2fs_has_inline_data(inode) || f2fs_has_inline_dentry(inode)) {
		if (whence == SEEK_HOLE)
			data_ofs = isize;
		goto found;
	}

	pgofs = (pgoff_t)(offset >> PAGE_SHIFT);

	dirty = __get_first_dirty_index(inode->i_mapping, pgofs, whence);

	for (; data_ofs < isize; data_ofs = (loff_t)pgofs << PAGE_SHIFT) {
		set_new_dnode(&dn, inode, NULL, NULL, 0);
		err = f2fs_get_dnode_of_data(&dn, pgofs, LOOKUP_NODE);
		if (err && err != -ENOENT) {
			goto fail;
		} else if (err == -ENOENT) {
			/* direct node does not exists */
			if (whence == SEEK_DATA) {
				pgofs = f2fs_get_next_page_offset(&dn, pgofs);
				continue;
			} else {
				goto found;
			}
		}

		end_offset = ADDRS_PER_PAGE(dn.node_page, inode);

		/* find data/hole in dnode block */
		for (; dn.ofs_in_node < end_offset;
				dn.ofs_in_node++, pgofs++,
				data_ofs = (loff_t)pgofs << PAGE_SHIFT) {
			block_t blkaddr;

			blkaddr = datablock_addr(dn.inode,
					dn.node_page, dn.ofs_in_node);

			if (__is_valid_data_blkaddr(blkaddr) &&
				!f2fs_is_valid_blkaddr(F2FS_I_SB(inode),
					blkaddr, DATA_GENERIC_ENHANCE)) {
				f2fs_put_dnode(&dn);
				goto fail;
			}

			if (__found_offset(F2FS_I_SB(inode), blkaddr, dirty,
							pgofs, whence)) {
				f2fs_put_dnode(&dn);
				goto found;
			}
		}
		f2fs_put_dnode(&dn);
	}

	if (whence == SEEK_DATA)
		goto fail;
found:
	if (whence == SEEK_HOLE && data_ofs > isize)
		data_ofs = isize;
	inode_unlock(inode);
	return vfs_setpos(file, data_ofs, maxbytes);
fail:
	inode_unlock(inode);
	return -ENXIO;
}