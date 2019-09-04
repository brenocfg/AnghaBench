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
struct summary_footer {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct curseg_info {int /*<<< orphan*/  segno; TYPE_1__* sum_blk; int /*<<< orphan*/  next_segno; scalar_t__ next_blkoff; int /*<<< orphan*/  zone; } ;
struct TYPE_2__ {struct summary_footer footer; } ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  GET_ZONE_FROM_SEG (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DATASEG (int) ; 
 scalar_t__ IS_NODESEG (int) ; 
 int /*<<< orphan*/  NULL_SEGNO ; 
 int /*<<< orphan*/  SET_SUM_TYPE (struct summary_footer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUM_TYPE_DATA ; 
 int /*<<< orphan*/  SUM_TYPE_NODE ; 
 int /*<<< orphan*/  __set_sit_entry_type (struct f2fs_sb_info*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct summary_footer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_curseg(struct f2fs_sb_info *sbi, int type, int modified)
{
	struct curseg_info *curseg = CURSEG_I(sbi, type);
	struct summary_footer *sum_footer;

	curseg->segno = curseg->next_segno;
	curseg->zone = GET_ZONE_FROM_SEG(sbi, curseg->segno);
	curseg->next_blkoff = 0;
	curseg->next_segno = NULL_SEGNO;

	sum_footer = &(curseg->sum_blk->footer);
	memset(sum_footer, 0, sizeof(struct summary_footer));
	if (IS_DATASEG(type))
		SET_SUM_TYPE(sum_footer, SUM_TYPE_DATA);
	if (IS_NODESEG(type))
		SET_SUM_TYPE(sum_footer, SUM_TYPE_NODE);
	__set_sit_entry_type(sbi, type, curseg->segno, modified);
}