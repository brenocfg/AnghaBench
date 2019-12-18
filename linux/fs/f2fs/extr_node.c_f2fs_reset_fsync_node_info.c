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
struct f2fs_sb_info {int /*<<< orphan*/  fsync_node_lock; scalar_t__ fsync_seg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void f2fs_reset_fsync_node_info(struct f2fs_sb_info *sbi)
{
	unsigned long flags;

	spin_lock_irqsave(&sbi->fsync_node_lock, flags);
	sbi->fsync_seg_id = 0;
	spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);
}