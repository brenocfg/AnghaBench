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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_fs_info {int dummy; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_WQ_ENDIO_DIO_REPAIR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ REQ_OP_WRITE ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ btrfs_bio_wq_end_io (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_map_bio (struct btrfs_fs_info*,struct bio*,int,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline blk_status_t submit_dio_repair_bio(struct inode *inode,
						 struct bio *bio,
						 int mirror_num)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	blk_status_t ret;

	BUG_ON(bio_op(bio) == REQ_OP_WRITE);

	ret = btrfs_bio_wq_end_io(fs_info, bio, BTRFS_WQ_ENDIO_DIO_REPAIR);
	if (ret)
		return ret;

	ret = btrfs_map_bio(fs_info, bio, mirror_num, 0);

	return ret;
}