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
struct f2fs_sb_info {int segs_per_sec; scalar_t__ s_ndevs; int /*<<< orphan*/  gc_pin_file_threshold; } ;
struct TYPE_6__ {int /*<<< orphan*/ * v_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  end_blk; } ;
struct TYPE_4__ {scalar_t__* last_victim; } ;

/* Variables and functions */
 size_t ALLOC_NEXT ; 
 int /*<<< orphan*/  DEF_GC_FAILED_PINNED_FILES ; 
 TYPE_3__* DIRTY_I (struct f2fs_sb_info*) ; 
 TYPE_2__ FDEV (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 TYPE_1__* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  default_v_ops ; 

void f2fs_build_gc_manager(struct f2fs_sb_info *sbi)
{
	DIRTY_I(sbi)->v_ops = &default_v_ops;

	sbi->gc_pin_file_threshold = DEF_GC_FAILED_PINNED_FILES;

	/* give warm/cold data area from slower device */
	if (sbi->s_ndevs && sbi->segs_per_sec == 1)
		SIT_I(sbi)->last_victim[ALLOC_NEXT] =
				GET_SEGNO(sbi, FDEV(0).end_blk) + 1;
}