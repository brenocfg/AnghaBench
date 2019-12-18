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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct f2fs_sb_info {int dummy; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_sem; int /*<<< orphan*/ * i_gc_rwsem; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int F2FS_BLKSIZE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t WRITE ; 
 int __exchange_data_block (struct inode*,struct inode*,int,int,int,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_drop_extent_tree (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int f2fs_truncate_blocks (struct inode*,int,int) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int inode_newsize_ok (struct inode*,int) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_insert_range(struct inode *inode, loff_t offset, loff_t len)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	pgoff_t nr, pg_start, pg_end, delta, idx;
	loff_t new_size;
	int ret = 0;

	new_size = i_size_read(inode) + len;
	ret = inode_newsize_ok(inode, new_size);
	if (ret)
		return ret;

	if (offset >= i_size_read(inode))
		return -EINVAL;

	/* insert range should be aligned to block size of f2fs. */
	if (offset & (F2FS_BLKSIZE - 1) || len & (F2FS_BLKSIZE - 1))
		return -EINVAL;

	ret = f2fs_convert_inline_inode(inode);
	if (ret)
		return ret;

	f2fs_balance_fs(sbi, true);

	down_write(&F2FS_I(inode)->i_mmap_sem);
	ret = f2fs_truncate_blocks(inode, i_size_read(inode), true);
	up_write(&F2FS_I(inode)->i_mmap_sem);
	if (ret)
		return ret;

	/* write out all dirty pages from offset */
	ret = filemap_write_and_wait_range(inode->i_mapping, offset, LLONG_MAX);
	if (ret)
		return ret;

	pg_start = offset >> PAGE_SHIFT;
	pg_end = (offset + len) >> PAGE_SHIFT;
	delta = pg_end - pg_start;
	idx = DIV_ROUND_UP(i_size_read(inode), PAGE_SIZE);

	/* avoid gc operation during block exchange */
	down_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
	down_write(&F2FS_I(inode)->i_mmap_sem);
	truncate_pagecache(inode, offset);

	while (!ret && idx > pg_start) {
		nr = idx - pg_start;
		if (nr > delta)
			nr = delta;
		idx -= nr;

		f2fs_lock_op(sbi);
		f2fs_drop_extent_tree(inode);

		ret = __exchange_data_block(inode, inode, idx,
					idx + delta, nr, false);
		f2fs_unlock_op(sbi);
	}
	up_write(&F2FS_I(inode)->i_mmap_sem);
	up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);

	/* write out all moved pages, if possible */
	down_write(&F2FS_I(inode)->i_mmap_sem);
	filemap_write_and_wait_range(inode->i_mapping, offset, LLONG_MAX);
	truncate_pagecache(inode, offset);
	up_write(&F2FS_I(inode)->i_mmap_sem);

	if (!ret)
		f2fs_i_size_write(inode, new_size);
	return ret;
}