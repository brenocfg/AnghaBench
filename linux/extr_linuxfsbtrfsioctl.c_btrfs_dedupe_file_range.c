#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_8__ {TYPE_3__* root; } ;
struct TYPE_7__ {TYPE_2__* fs_info; } ;
struct TYPE_6__ {TYPE_1__* sb; } ;
struct TYPE_5__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int btrfs_extent_same (struct inode*,int /*<<< orphan*/ ,scalar_t__,struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 

int btrfs_dedupe_file_range(struct file *src_file, loff_t src_loff,
			    struct file *dst_file, loff_t dst_loff,
			    u64 olen)
{
	struct inode *src = file_inode(src_file);
	struct inode *dst = file_inode(dst_file);
	u64 bs = BTRFS_I(src)->root->fs_info->sb->s_blocksize;

	if (WARN_ON_ONCE(bs < PAGE_SIZE)) {
		/*
		 * Btrfs does not support blocksize < page_size. As a
		 * result, btrfs_cmp_data() won't correctly handle
		 * this situation without an update.
		 */
		return -EINVAL;
	}

	return btrfs_extent_same(src, src_loff, olen, dst, dst_loff);
}