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
struct inode {struct address_space* i_mapping; } ;
struct f2fs_sb_info {int dummy; } ;
struct address_space {int dummy; } ;
typedef  unsigned long long pgoff_t ;
typedef  unsigned long long loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * i_gc_rwsem; int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 unsigned long long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 size_t WRITE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 int f2fs_truncate_hole (struct inode*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int fill_zero (struct inode*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (struct address_space*,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int punch_hole(struct inode *inode, loff_t offset, loff_t len)
{
	pgoff_t pg_start, pg_end;
	loff_t off_start, off_end;
	int ret;

	ret = f2fs_convert_inline_inode(inode);
	if (ret)
		return ret;

	pg_start = ((unsigned long long) offset) >> PAGE_SHIFT;
	pg_end = ((unsigned long long) offset + len) >> PAGE_SHIFT;

	off_start = offset & (PAGE_SIZE - 1);
	off_end = (offset + len) & (PAGE_SIZE - 1);

	if (pg_start == pg_end) {
		ret = fill_zero(inode, pg_start, off_start,
						off_end - off_start);
		if (ret)
			return ret;
	} else {
		if (off_start) {
			ret = fill_zero(inode, pg_start++, off_start,
						PAGE_SIZE - off_start);
			if (ret)
				return ret;
		}
		if (off_end) {
			ret = fill_zero(inode, pg_end, 0, off_end);
			if (ret)
				return ret;
		}

		if (pg_start < pg_end) {
			struct address_space *mapping = inode->i_mapping;
			loff_t blk_start, blk_end;
			struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

			f2fs_balance_fs(sbi, true);

			blk_start = (loff_t)pg_start << PAGE_SHIFT;
			blk_end = (loff_t)pg_end << PAGE_SHIFT;

			down_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
			down_write(&F2FS_I(inode)->i_mmap_sem);

			truncate_inode_pages_range(mapping, blk_start,
					blk_end - 1);

			f2fs_lock_op(sbi);
			ret = f2fs_truncate_hole(inode, pg_start, pg_end);
			f2fs_unlock_op(sbi);

			up_write(&F2FS_I(inode)->i_mmap_sem);
			up_write(&F2FS_I(inode)->i_gc_rwsem[WRITE]);
		}
	}

	return ret;
}