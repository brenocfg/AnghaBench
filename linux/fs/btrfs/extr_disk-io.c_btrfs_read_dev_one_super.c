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
typedef  int u64 ;
struct buffer_head {scalar_t__ b_data; } ;
struct btrfs_super_block {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int BTRFS_BDEV_BLOCKSIZE ; 
 scalar_t__ BTRFS_MAGIC ; 
 scalar_t__ BTRFS_SUPER_INFO_SIZE ; 
 int EINVAL ; 
 int EIO ; 
 struct buffer_head* __bread (struct block_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int btrfs_sb_offset (int) ; 
 int btrfs_super_bytenr (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_magic (struct btrfs_super_block*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

int btrfs_read_dev_one_super(struct block_device *bdev, int copy_num,
			struct buffer_head **bh_ret)
{
	struct buffer_head *bh;
	struct btrfs_super_block *super;
	u64 bytenr;

	bytenr = btrfs_sb_offset(copy_num);
	if (bytenr + BTRFS_SUPER_INFO_SIZE >= i_size_read(bdev->bd_inode))
		return -EINVAL;

	bh = __bread(bdev, bytenr / BTRFS_BDEV_BLOCKSIZE, BTRFS_SUPER_INFO_SIZE);
	/*
	 * If we fail to read from the underlying devices, as of now
	 * the best option we have is to mark it EIO.
	 */
	if (!bh)
		return -EIO;

	super = (struct btrfs_super_block *)bh->b_data;
	if (btrfs_super_bytenr(super) != bytenr ||
		    btrfs_super_magic(super) != BTRFS_MAGIC) {
		brelse(bh);
		return -EINVAL;
	}

	*bh_ret = bh;
	return 0;
}