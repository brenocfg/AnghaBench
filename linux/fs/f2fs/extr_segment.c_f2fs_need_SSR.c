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
struct f2fs_sb_info {scalar_t__ gc_mode; } ;
struct TYPE_2__ {scalar_t__ min_ssr_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_DIRTY_DENTS ; 
 int /*<<< orphan*/  F2FS_DIRTY_IMETA ; 
 int /*<<< orphan*/  F2FS_DIRTY_NODES ; 
 scalar_t__ GC_URGENT ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 scalar_t__ free_sections (struct f2fs_sb_info*) ; 
 int get_blocktype_secs (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ reserved_sections (struct f2fs_sb_info*) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

bool f2fs_need_SSR(struct f2fs_sb_info *sbi)
{
	int node_secs = get_blocktype_secs(sbi, F2FS_DIRTY_NODES);
	int dent_secs = get_blocktype_secs(sbi, F2FS_DIRTY_DENTS);
	int imeta_secs = get_blocktype_secs(sbi, F2FS_DIRTY_IMETA);

	if (test_opt(sbi, LFS))
		return false;
	if (sbi->gc_mode == GC_URGENT)
		return true;
	if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED)))
		return true;

	return free_sections(sbi) <= (node_secs + 2 * dent_secs + imeta_secs +
			SM_I(sbi)->min_ssr_sections + reserved_sections(sbi));
}