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
struct seg_entry {scalar_t__ valid_blocks; } ;
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  segno; } ;
struct TYPE_2__ {int /*<<< orphan*/  written_valid_blocks; } ;

/* Variables and functions */
 int CURSEG_COLD_NODE ; 
 int CURSEG_HOT_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 unsigned int MAIN_SEGS (struct f2fs_sb_info*) ; 
 TYPE_1__* SIT_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __set_free (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  __set_test_and_inuse (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 struct seg_entry* get_seg_entry (struct f2fs_sb_info*,unsigned int) ; 

__attribute__((used)) static void init_free_segmap(struct f2fs_sb_info *sbi)
{
	unsigned int start;
	int type;

	for (start = 0; start < MAIN_SEGS(sbi); start++) {
		struct seg_entry *sentry = get_seg_entry(sbi, start);
		if (!sentry->valid_blocks)
			__set_free(sbi, start);
		else
			SIT_I(sbi)->written_valid_blocks +=
						sentry->valid_blocks;
	}

	/* set use the current segments */
	for (type = CURSEG_HOT_DATA; type <= CURSEG_COLD_NODE; type++) {
		struct curseg_info *curseg_t = CURSEG_I(sbi, type);
		__set_test_and_inuse(sbi, curseg_t->segno);
	}
}