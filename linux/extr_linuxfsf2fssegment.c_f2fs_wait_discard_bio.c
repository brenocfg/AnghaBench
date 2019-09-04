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
struct discard_cmd_control {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  root; } ;
struct discard_cmd {scalar_t__ state; int /*<<< orphan*/  ref; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 scalar_t__ D_PREP ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __punch_discard_cmd (struct f2fs_sb_info*,struct discard_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wait_one_discard_bio (struct f2fs_sb_info*,struct discard_cmd*) ; 
 scalar_t__ f2fs_lookup_rb_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void f2fs_wait_discard_bio(struct f2fs_sb_info *sbi, block_t blkaddr)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct discard_cmd *dc;
	bool need_wait = false;

	mutex_lock(&dcc->cmd_lock);
	dc = (struct discard_cmd *)f2fs_lookup_rb_tree(&dcc->root,
							NULL, blkaddr);
	if (dc) {
		if (dc->state == D_PREP) {
			__punch_discard_cmd(sbi, dc, blkaddr);
		} else {
			dc->ref++;
			need_wait = true;
		}
	}
	mutex_unlock(&dcc->cmd_lock);

	if (need_wait)
		__wait_one_discard_bio(sbi, dc);
}