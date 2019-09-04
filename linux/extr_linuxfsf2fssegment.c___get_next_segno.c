#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct f2fs_sb_info {int segs_per_sec; } ;
struct TYPE_6__ {unsigned int segno; } ;
struct TYPE_5__ {scalar_t__ alloc_mode; } ;
struct TYPE_4__ {unsigned int* last_victim; } ;

/* Variables and functions */
 scalar_t__ ALLOC_MODE_REUSE ; 
 size_t ALLOC_NEXT ; 
 int CURSEG_HOT_DATA ; 
 TYPE_3__* CURSEG_I (struct f2fs_sb_info*,int) ; 
 TYPE_2__ F2FS_OPTION (struct f2fs_sb_info*) ; 
 scalar_t__ IS_NODESEG (int) ; 
 int /*<<< orphan*/  NOHEAP ; 
 TYPE_1__* SIT_I (struct f2fs_sb_info*) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int __get_next_segno(struct f2fs_sb_info *sbi, int type)
{
	/* if segs_per_sec is large than 1, we need to keep original policy. */
	if (sbi->segs_per_sec != 1)
		return CURSEG_I(sbi, type)->segno;

	if (test_opt(sbi, NOHEAP) &&
		(type == CURSEG_HOT_DATA || IS_NODESEG(type)))
		return 0;

	if (SIT_I(sbi)->last_victim[ALLOC_NEXT])
		return SIT_I(sbi)->last_victim[ALLOC_NEXT];

	/* find segments from 0 to reuse freed segments */
	if (F2FS_OPTION(sbi).alloc_mode == ALLOC_MODE_REUSE)
		return 0;

	return CURSEG_I(sbi, type)->segno;
}