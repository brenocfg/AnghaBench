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
typedef  scalar_t__ u64 ;
struct buffer_head {scalar_t__ b_data; } ;
struct btrfs_super_block {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct buffer_head* ERR_PTR (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int btrfs_read_dev_one_super (struct block_device*,int,struct buffer_head**) ; 
 scalar_t__ btrfs_super_generation (struct btrfs_super_block*) ; 

struct buffer_head *btrfs_read_dev_super(struct block_device *bdev)
{
	struct buffer_head *bh;
	struct buffer_head *latest = NULL;
	struct btrfs_super_block *super;
	int i;
	u64 transid = 0;
	int ret = -EINVAL;

	/* we would like to check all the supers, but that would make
	 * a btrfs mount succeed after a mkfs from a different FS.
	 * So, we need to add a special mount option to scan for
	 * later supers, using BTRFS_SUPER_MIRROR_MAX instead
	 */
	for (i = 0; i < 1; i++) {
		ret = btrfs_read_dev_one_super(bdev, i, &bh);
		if (ret)
			continue;

		super = (struct btrfs_super_block *)bh->b_data;

		if (!latest || btrfs_super_generation(super) > transid) {
			brelse(latest);
			latest = bh;
			transid = btrfs_super_generation(super);
		} else {
			brelse(bh);
		}
	}

	if (!latest)
		return ERR_PTR(ret);

	return latest;
}