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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  EXT2_I (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_DAX (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  NOBH ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ext2_truncate_blocks (struct inode*,scalar_t__) ; 
 int block_truncate_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dax_sem_down_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_sem_up_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_get_block ; 
 scalar_t__ ext2_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/  ext2_iomap_ops ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 scalar_t__ inode_needs_sync (struct inode*) ; 
 int iomap_zero_range (struct inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int nobh_truncate_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_inode_metadata (struct inode*,int) ; 
 int /*<<< orphan*/  sync_mapping_buffers (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 

__attribute__((used)) static int ext2_setsize(struct inode *inode, loff_t newsize)
{
	int error;

	if (!(S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
	    S_ISLNK(inode->i_mode)))
		return -EINVAL;
	if (ext2_inode_is_fast_symlink(inode))
		return -EINVAL;
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		return -EPERM;

	inode_dio_wait(inode);

	if (IS_DAX(inode)) {
		error = iomap_zero_range(inode, newsize,
					 PAGE_ALIGN(newsize) - newsize, NULL,
					 &ext2_iomap_ops);
	} else if (test_opt(inode->i_sb, NOBH))
		error = nobh_truncate_page(inode->i_mapping,
				newsize, ext2_get_block);
	else
		error = block_truncate_page(inode->i_mapping,
				newsize, ext2_get_block);
	if (error)
		return error;

	dax_sem_down_write(EXT2_I(inode));
	truncate_setsize(inode, newsize);
	__ext2_truncate_blocks(inode, newsize);
	dax_sem_up_write(EXT2_I(inode));

	inode->i_mtime = inode->i_ctime = current_time(inode);
	if (inode_needs_sync(inode)) {
		sync_mapping_buffers(inode->i_mapping);
		sync_inode_metadata(inode, 1);
	} else {
		mark_inode_dirty(inode);
	}

	return 0;
}