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
struct discard_cmd_control {int /*<<< orphan*/  discard_cmd_cnt; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_issue_discard_timeout (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_stop_discard_thread (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  kvfree (struct discard_cmd_control*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_discard_cmd_control(struct f2fs_sb_info *sbi)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;

	if (!dcc)
		return;

	f2fs_stop_discard_thread(sbi);

	/*
	 * Recovery can cache discard commands, so in error path of
	 * fill_super(), it needs to give a chance to handle them.
	 */
	if (unlikely(atomic_read(&dcc->discard_cmd_cnt)))
		f2fs_issue_discard_timeout(sbi);

	kvfree(dcc);
	SM_I(sbi)->dcc_info = NULL;
}