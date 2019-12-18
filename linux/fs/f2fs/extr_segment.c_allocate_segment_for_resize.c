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
struct curseg_info {unsigned int segno; int /*<<< orphan*/  curseg_mutex; } ;
struct TYPE_4__ {int /*<<< orphan*/  sentry_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  curseg_lock; } ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 TYPE_2__* SIT_I (struct f2fs_sb_info*) ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  change_curseg (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ f2fs_need_SSR (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_notice (struct f2fs_sb_info*,char*,int,unsigned int,unsigned int) ; 
 scalar_t__ get_ssr_segment (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  locate_dirty_segment (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_curseg (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  stat_inc_seg_type (struct f2fs_sb_info*,struct curseg_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void allocate_segment_for_resize(struct f2fs_sb_info *sbi, int type,
					unsigned int start, unsigned int end)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);
	unsigned int segno;

	down_read(&SM_I(sbi)->curseg_lock);
	mutex_lock(&curseg->curseg_mutex);
	down_write(&SIT_I(sbi)->sentry_lock);

	segno = CURSEG_I(sbi, type)->segno;
	if (segno < start || segno > end)
		goto unlock;

	if (f2fs_need_SSR(sbi) && get_ssr_segment(sbi, type))
		change_curseg(sbi, type);
	else
		new_curseg(sbi, type, true);

	stat_inc_seg_type(sbi, curseg);

	locate_dirty_segment(sbi, segno);
unlock:
	up_write(&SIT_I(sbi)->sentry_lock);

	if (segno != curseg->segno)
		f2fs_notice(sbi, "For resize: curseg of type %d: %u ==> %u",
			    type, segno, curseg->segno);

	mutex_unlock(&curseg->curseg_mutex);
	up_read(&SM_I(sbi)->curseg_lock);
}