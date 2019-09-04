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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_dio_private {int dummy; } ;
struct bio {struct btrfs_dio_private* bi_private; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  sync_writers; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int BTRFS_INODE_NODATASUM ; 
 int /*<<< orphan*/  BTRFS_WQ_ENDIO_DATA ; 
 scalar_t__ REQ_OP_WRITE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bio_op (struct bio*) ; 
 scalar_t__ btrfs_bio_wq_end_io (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_csum_one_bio (struct inode*,struct bio*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ btrfs_lookup_and_bind_dio_csum (struct inode*,struct btrfs_dio_private*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_map_bio (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_submit_bio_start_direct_io ; 
 scalar_t__ btrfs_wq_submit_bio (struct btrfs_fs_info*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline blk_status_t btrfs_submit_dio_bio(struct bio *bio,
		struct inode *inode, u64 file_offset, int async_submit)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_dio_private *dip = bio->bi_private;
	bool write = bio_op(bio) == REQ_OP_WRITE;
	blk_status_t ret;

	/* Check btrfs_submit_bio_hook() for rules about async submit. */
	if (async_submit)
		async_submit = !atomic_read(&BTRFS_I(inode)->sync_writers);

	if (!write) {
		ret = btrfs_bio_wq_end_io(fs_info, bio, BTRFS_WQ_ENDIO_DATA);
		if (ret)
			goto err;
	}

	if (BTRFS_I(inode)->flags & BTRFS_INODE_NODATASUM)
		goto map;

	if (write && async_submit) {
		ret = btrfs_wq_submit_bio(fs_info, bio, 0, 0,
					  file_offset, inode,
					  btrfs_submit_bio_start_direct_io);
		goto err;
	} else if (write) {
		/*
		 * If we aren't doing async submit, calculate the csum of the
		 * bio now.
		 */
		ret = btrfs_csum_one_bio(inode, bio, file_offset, 1);
		if (ret)
			goto err;
	} else {
		ret = btrfs_lookup_and_bind_dio_csum(inode, dip, bio,
						     file_offset);
		if (ret)
			goto err;
	}
map:
	ret = btrfs_map_bio(fs_info, bio, 0, 0);
err:
	return ret;
}