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
struct request_list {scalar_t__* count; } ;
struct request_queue {struct request_list root_rl; } ;
struct f2fs_sb_info {TYPE_1__* sb; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct block_device* s_bdev; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int /*<<< orphan*/  REQ_TIME ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int f2fs_time_over (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_idle(struct f2fs_sb_info *sbi)
{
	struct block_device *bdev = sbi->sb->s_bdev;
	struct request_queue *q = bdev_get_queue(bdev);
	struct request_list *rl = &q->root_rl;

	if (rl->count[BLK_RW_SYNC] || rl->count[BLK_RW_ASYNC])
		return false;

	return f2fs_time_over(sbi, REQ_TIME);
}