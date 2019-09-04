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
struct f2fs_sb_info {TYPE_1__* sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bdev_get_queue (int /*<<< orphan*/ ) ; 
 int blk_queue_discard (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_hw_support_discard(struct f2fs_sb_info *sbi)
{
	return blk_queue_discard(bdev_get_queue(sbi->sb->s_bdev));
}