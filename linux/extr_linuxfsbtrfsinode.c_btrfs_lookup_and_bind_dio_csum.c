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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {TYPE_1__* i_sb; } ;
struct btrfs_io_bio {int /*<<< orphan*/ * csum; } ;
struct btrfs_dio_private {scalar_t__ logical_offset; struct bio* orig_bio; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_2__ {scalar_t__ s_blocksize_bits; } ;

/* Variables and functions */
 struct btrfs_io_bio* btrfs_io_bio (struct bio*) ; 
 scalar_t__ btrfs_lookup_bio_sums_dio (struct inode*,struct bio*,scalar_t__) ; 

__attribute__((used)) static inline blk_status_t btrfs_lookup_and_bind_dio_csum(struct inode *inode,
						 struct btrfs_dio_private *dip,
						 struct bio *bio,
						 u64 file_offset)
{
	struct btrfs_io_bio *io_bio = btrfs_io_bio(bio);
	struct btrfs_io_bio *orig_io_bio = btrfs_io_bio(dip->orig_bio);
	blk_status_t ret;

	/*
	 * We load all the csum data we need when we submit
	 * the first bio to reduce the csum tree search and
	 * contention.
	 */
	if (dip->logical_offset == file_offset) {
		ret = btrfs_lookup_bio_sums_dio(inode, dip->orig_bio,
						file_offset);
		if (ret)
			return ret;
	}

	if (bio == dip->orig_bio)
		return 0;

	file_offset -= dip->logical_offset;
	file_offset >>= inode->i_sb->s_blocksize_bits;
	io_bio->csum = (u8 *)(((u32 *)orig_io_bio->csum) + file_offset);

	return 0;
}