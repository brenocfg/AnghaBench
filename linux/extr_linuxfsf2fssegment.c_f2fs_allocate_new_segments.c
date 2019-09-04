#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {unsigned int segno; } ;
struct TYPE_4__ {int /*<<< orphan*/  sentry_lock; TYPE_1__* s_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* allocate_segment ) (struct f2fs_sb_info*,int,int) ;} ;

/* Variables and functions */
 int CURSEG_COLD_DATA ; 
 int CURSEG_HOT_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 TYPE_2__* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locate_dirty_segment (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void f2fs_allocate_new_segments(struct f2fs_sb_info *sbi)
{
	struct curseg_info *curseg;
	unsigned int old_segno;
	int i;

	down_write(&SIT_I(sbi)->sentry_lock);

	for (i = CURSEG_HOT_DATA; i <= CURSEG_COLD_DATA; i++) {
		curseg = CURSEG_I(sbi, i);
		old_segno = curseg->segno;
		SIT_I(sbi)->s_ops->allocate_segment(sbi, i, true);
		locate_dirty_segment(sbi, old_segno);
	}

	up_write(&SIT_I(sbi)->sentry_lock);
}