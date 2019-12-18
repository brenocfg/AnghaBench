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
struct victim_selection {scalar_t__ (* get_victim ) (struct f2fs_sb_info*,unsigned int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {unsigned int next_segno; } ;
struct TYPE_2__ {struct victim_selection* v_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  BG_GC ; 
 int CURSEG_COLD_DATA ; 
 int CURSEG_COLD_NODE ; 
 int CURSEG_HOT_DATA ; 
 int CURSEG_HOT_NODE ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int CURSEG_WARM_DATA ; 
 int CURSEG_WARM_NODE ; 
 TYPE_1__* DIRTY_I (struct f2fs_sb_info*) ; 
 scalar_t__ IS_NODESEG (int) ; 
 int NR_CURSEG_DATA_TYPE ; 
 int NR_CURSEG_NODE_TYPE ; 
 unsigned int NULL_SEGNO ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SSR ; 
 unsigned int get_free_segment (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct f2fs_sb_info*,unsigned int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct f2fs_sb_info*,unsigned int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_ssr_segment(struct f2fs_sb_info *sbi, int type)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);
	const struct victim_selection *v_ops = DIRTY_I(sbi)->v_ops;
	unsigned segno = NULL_SEGNO;
	int i, cnt;
	bool reversed = false;

	/* f2fs_need_SSR() already forces to do this */
	if (v_ops->get_victim(sbi, &segno, BG_GC, type, SSR)) {
		curseg->next_segno = segno;
		return 1;
	}

	/* For node segments, let's do SSR more intensively */
	if (IS_NODESEG(type)) {
		if (type >= CURSEG_WARM_NODE) {
			reversed = true;
			i = CURSEG_COLD_NODE;
		} else {
			i = CURSEG_HOT_NODE;
		}
		cnt = NR_CURSEG_NODE_TYPE;
	} else {
		if (type >= CURSEG_WARM_DATA) {
			reversed = true;
			i = CURSEG_COLD_DATA;
		} else {
			i = CURSEG_HOT_DATA;
		}
		cnt = NR_CURSEG_DATA_TYPE;
	}

	for (; cnt-- > 0; reversed ? i-- : i++) {
		if (i == type)
			continue;
		if (v_ops->get_victim(sbi, &segno, BG_GC, i, SSR)) {
			curseg->next_segno = segno;
			return 1;
		}
	}

	/* find valid_blocks=0 in dirty list */
	if (unlikely(is_sbi_flag_set(sbi, SBI_CP_DISABLED))) {
		segno = get_free_segment(sbi);
		if (segno != NULL_SEGNO) {
			curseg->next_segno = segno;
			return 1;
		}
	}
	return 0;
}