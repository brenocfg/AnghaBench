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
struct f2fs_sm_info {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * sm_info; } ;

/* Variables and functions */
 struct f2fs_sm_info* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_curseg (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_dirty_segmap (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_discard_cmd_control (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_free_segmap (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  destroy_sit_info (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_destroy_flush_cmd_control (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  kvfree (struct f2fs_sm_info*) ; 

void f2fs_destroy_segment_manager(struct f2fs_sb_info *sbi)
{
	struct f2fs_sm_info *sm_info = SM_I(sbi);

	if (!sm_info)
		return;
	f2fs_destroy_flush_cmd_control(sbi, true);
	destroy_discard_cmd_control(sbi);
	destroy_dirty_segmap(sbi);
	destroy_curseg(sbi);
	destroy_free_segmap(sbi);
	destroy_sit_info(sbi);
	sbi->sm_info = NULL;
	kvfree(sm_info);
}