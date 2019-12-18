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
struct f2fs_sb_info {int dummy; } ;
struct block_device {int dummy; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int __f2fs_issue_discard_zone (struct f2fs_sb_info*,struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __queue_discard_cmd (struct f2fs_sb_info*,struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bdev_is_zoned (struct block_device*) ; 
 scalar_t__ f2fs_sb_has_blkzoned (struct f2fs_sb_info*) ; 

__attribute__((used)) static int __issue_discard_async(struct f2fs_sb_info *sbi,
		struct block_device *bdev, block_t blkstart, block_t blklen)
{
#ifdef CONFIG_BLK_DEV_ZONED
	if (f2fs_sb_has_blkzoned(sbi) && bdev_is_zoned(bdev))
		return __f2fs_issue_discard_zone(sbi, bdev, blkstart, blklen);
#endif
	return __queue_discard_cmd(sbi, bdev, blkstart, blklen);
}