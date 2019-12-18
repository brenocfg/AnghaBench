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
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_WQ_ENDIO_METADATA ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ btree_csum_one_bio (struct bio*) ; 
 int /*<<< orphan*/  btree_submit_bio_start ; 
 scalar_t__ btrfs_bio_wq_end_io (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_map_bio (struct btrfs_fs_info*,struct bio*,int,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_wq_submit_bio (struct btrfs_fs_info*,struct bio*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 
 int check_async_write (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t btree_submit_bio_hook(struct inode *inode, struct bio *bio,
					  int mirror_num,
					  unsigned long bio_flags)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	int async = check_async_write(fs_info, BTRFS_I(inode));
	blk_status_t ret;

	if (bio_op(bio) != REQ_OP_WRITE) {
		/*
		 * called for a read, do the setup so that checksum validation
		 * can happen in the async kernel threads
		 */
		ret = btrfs_bio_wq_end_io(fs_info, bio,
					  BTRFS_WQ_ENDIO_METADATA);
		if (ret)
			goto out_w_error;
		ret = btrfs_map_bio(fs_info, bio, mirror_num, 0);
	} else if (!async) {
		ret = btree_csum_one_bio(bio);
		if (ret)
			goto out_w_error;
		ret = btrfs_map_bio(fs_info, bio, mirror_num, 0);
	} else {
		/*
		 * kthread helpers are used to submit writes so that
		 * checksumming can happen in parallel across all CPUs
		 */
		ret = btrfs_wq_submit_bio(fs_info, bio, mirror_num, 0,
					  0, inode, btree_submit_bio_start);
	}

	if (ret)
		goto out_w_error;
	return 0;

out_w_error:
	bio->bi_status = ret;
	bio_endio(bio);
	return ret;
}