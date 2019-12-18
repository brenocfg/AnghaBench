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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_csum_one_bio (struct inode*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t btrfs_submit_bio_start(void *private_data, struct bio *bio,
				    u64 bio_offset)
{
	struct inode *inode = private_data;
	blk_status_t ret = 0;

	ret = btrfs_csum_one_bio(inode, bio, 0, 0);
	BUG_ON(ret); /* -ENOMEM */
	return 0;
}