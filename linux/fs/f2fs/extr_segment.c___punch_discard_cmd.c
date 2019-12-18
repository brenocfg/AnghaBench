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
struct f2fs_sb_info {int dummy; } ;
struct discard_info {int len; int lstart; int start; } ;
struct discard_cmd_control {int undiscard_blks; } ;
struct discard_cmd {scalar_t__ state; int len; int lstart; int /*<<< orphan*/  start; int /*<<< orphan*/  bdev; struct discard_info di; } ;
typedef  int block_t ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 scalar_t__ D_DONE ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __insert_discard_tree (struct f2fs_sb_info*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __relocate_discard_cmd (struct discard_cmd_control*,struct discard_cmd*) ; 
 int /*<<< orphan*/  __remove_discard_cmd (struct f2fs_sb_info*,struct discard_cmd*) ; 

__attribute__((used)) static void __punch_discard_cmd(struct f2fs_sb_info *sbi,
				struct discard_cmd *dc, block_t blkaddr)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct discard_info di = dc->di;
	bool modified = false;

	if (dc->state == D_DONE || dc->len == 1) {
		__remove_discard_cmd(sbi, dc);
		return;
	}

	dcc->undiscard_blks -= di.len;

	if (blkaddr > di.lstart) {
		dc->len = blkaddr - dc->lstart;
		dcc->undiscard_blks += dc->len;
		__relocate_discard_cmd(dcc, dc);
		modified = true;
	}

	if (blkaddr < di.lstart + di.len - 1) {
		if (modified) {
			__insert_discard_tree(sbi, dc->bdev, blkaddr + 1,
					di.start + blkaddr + 1 - di.lstart,
					di.lstart + di.len - 1 - blkaddr,
					NULL, NULL);
		} else {
			dc->lstart++;
			dc->len--;
			dc->start++;
			dcc->undiscard_blks += dc->len;
			__relocate_discard_cmd(dcc, dc);
		}
	}
}