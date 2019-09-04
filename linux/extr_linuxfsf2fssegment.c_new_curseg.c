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
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {unsigned int segno; unsigned int next_segno; int /*<<< orphan*/  alloc_type; int /*<<< orphan*/  sum_blk; } ;

/* Variables and functions */
 int ALLOC_LEFT ; 
 int ALLOC_RIGHT ; 
 int CURSEG_COLD_DATA ; 
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int CURSEG_WARM_DATA ; 
 int /*<<< orphan*/  GET_SUM_BLOCK (struct f2fs_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  NOHEAP ; 
 unsigned int __get_next_segno (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  get_new_segment (struct f2fs_sb_info*,unsigned int*,int,int) ; 
 int /*<<< orphan*/  reset_curseg (struct f2fs_sb_info*,int,int) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sum_page (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void new_curseg(struct f2fs_sb_info *sbi, int type, bool new_sec)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);
	unsigned int segno = curseg->segno;
	int dir = ALLOC_LEFT;

	write_sum_page(sbi, curseg->sum_blk,
				GET_SUM_BLOCK(sbi, segno));
	if (type == CURSEG_WARM_DATA || type == CURSEG_COLD_DATA)
		dir = ALLOC_RIGHT;

	if (test_opt(sbi, NOHEAP))
		dir = ALLOC_RIGHT;

	segno = __get_next_segno(sbi, type);
	get_new_segment(sbi, &segno, new_sec, dir);
	curseg->next_segno = segno;
	reset_curseg(sbi, type, 1);
	curseg->alloc_type = LFS;
}