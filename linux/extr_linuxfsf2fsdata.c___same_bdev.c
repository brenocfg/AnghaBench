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
struct block_device {scalar_t__ bd_disk; scalar_t__ bd_partno; } ;
struct bio {scalar_t__ bi_disk; scalar_t__ bi_partno; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 struct block_device* f2fs_target_device (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool __same_bdev(struct f2fs_sb_info *sbi,
				block_t blk_addr, struct bio *bio)
{
	struct block_device *b = f2fs_target_device(sbi, blk_addr, NULL);
	return bio->bi_disk == b->bd_disk && bio->bi_partno == b->bd_partno;
}