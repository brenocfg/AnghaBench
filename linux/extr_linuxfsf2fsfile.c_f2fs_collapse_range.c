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
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int F2FS_BLKSIZE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  LLONG_MAX ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int f2fs_do_collapse (struct inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  f2fs_i_size_write (struct inode*,scalar_t__) ; 
 int f2fs_truncate_blocks (struct inode*,scalar_t__,int) ; 
 int filemap_write_and_wait_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f2fs_collapse_range(struct inode *inode, loff_t offset, loff_t len)
{
	loff_t new_size;
	int ret;

	if (offset + len >= i_size_read(inode))
		return -EINVAL;

	/* collapse range should be aligned to block size of f2fs. */
	if (offset & (F2FS_BLKSIZE - 1) || len & (F2FS_BLKSIZE - 1))
		return -EINVAL;

	ret = f2fs_convert_inline_inode(inode);
	if (ret)
		return ret;

	/* write out all dirty pages from offset */
	ret = filemap_write_and_wait_range(inode->i_mapping, offset, LLONG_MAX);
	if (ret)
		return ret;

	ret = f2fs_do_collapse(inode, offset, len);
	if (ret)
		return ret;

	/* write out all moved pages, if possible */
	down_write(&F2FS_I(inode)->i_mmap_sem);
	filemap_write_and_wait_range(inode->i_mapping, offset, LLONG_MAX);
	truncate_pagecache(inode, offset);

	new_size = i_size_read(inode) - len;
	truncate_pagecache(inode, new_size);

	ret = f2fs_truncate_blocks(inode, new_size, true);
	up_write(&F2FS_I(inode)->i_mmap_sem);
	if (!ret)
		f2fs_i_size_write(inode, new_size);
	return ret;
}