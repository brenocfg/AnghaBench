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
struct f2fs_sb_info {scalar_t__ fsync_node_num; scalar_t__ fsync_seg_id; int /*<<< orphan*/  fsync_node_list; int /*<<< orphan*/  fsync_node_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void f2fs_init_fsync_node_info(struct f2fs_sb_info *sbi)
{
	spin_lock_init(&sbi->fsync_node_lock);
	INIT_LIST_HEAD(&sbi->fsync_node_list);
	sbi->fsync_seg_id = 0;
	sbi->fsync_node_num = 0;
}