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
struct f2fs_sb_info {scalar_t__ gc_mode; } ;
struct TYPE_6__ {TYPE_2__* fcc_info; TYPE_1__* dcc_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  queued_flush; } ;
struct TYPE_4__ {int /*<<< orphan*/  queued_discard; } ;

/* Variables and functions */
 int DISCARD_TIME ; 
 int /*<<< orphan*/  F2FS_DIO_READ ; 
 int /*<<< orphan*/  F2FS_DIO_WRITE ; 
 int /*<<< orphan*/  F2FS_RD_DATA ; 
 int /*<<< orphan*/  F2FS_RD_META ; 
 int /*<<< orphan*/  F2FS_RD_NODE ; 
 int /*<<< orphan*/  F2FS_WB_CP_DATA ; 
 int /*<<< orphan*/  F2FS_WB_DATA ; 
 scalar_t__ GC_URGENT ; 
 TYPE_3__* SM_I (struct f2fs_sb_info*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int f2fs_time_over (struct f2fs_sb_info*,int) ; 
 scalar_t__ get_pages (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_idle(struct f2fs_sb_info *sbi, int type)
{
	if (sbi->gc_mode == GC_URGENT)
		return true;

	if (get_pages(sbi, F2FS_RD_DATA) || get_pages(sbi, F2FS_RD_NODE) ||
		get_pages(sbi, F2FS_RD_META) || get_pages(sbi, F2FS_WB_DATA) ||
		get_pages(sbi, F2FS_WB_CP_DATA) ||
		get_pages(sbi, F2FS_DIO_READ) ||
		get_pages(sbi, F2FS_DIO_WRITE))
		return false;

	if (type != DISCARD_TIME && SM_I(sbi) && SM_I(sbi)->dcc_info &&
			atomic_read(&SM_I(sbi)->dcc_info->queued_discard))
		return false;

	if (SM_I(sbi) && SM_I(sbi)->fcc_info &&
			atomic_read(&SM_I(sbi)->fcc_info->queued_flush))
		return false;

	return f2fs_time_over(sbi, type);
}