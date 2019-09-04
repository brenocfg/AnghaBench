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
struct bio {scalar_t__ bi_status; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ btrfs_map_bio (struct btrfs_fs_info*,struct bio*,int,int) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 

blk_status_t btrfs_submit_bio_done(void *private_data, struct bio *bio,
			  int mirror_num)
{
	struct inode *inode = private_data;
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	blk_status_t ret;

	ret = btrfs_map_bio(fs_info, bio, mirror_num, 1);
	if (ret) {
		bio->bi_status = ret;
		bio_endio(bio);
	}
	return ret;
}