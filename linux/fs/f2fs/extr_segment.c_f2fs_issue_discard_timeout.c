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
struct discard_policy {int /*<<< orphan*/  timeout; } ;
struct discard_cmd_control {int /*<<< orphan*/  discard_cmd_cnt; int /*<<< orphan*/  discard_granularity; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPOLICY_UMOUNT ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  UMOUNT_DISCARD_TIMEOUT ; 
 int __drop_discard_cmd (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __init_discard_policy (struct f2fs_sb_info*,struct discard_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __issue_discard_cmd (struct f2fs_sb_info*,struct discard_policy*) ; 
 int /*<<< orphan*/  __wait_all_discard_cmd (struct f2fs_sb_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

bool f2fs_issue_discard_timeout(struct f2fs_sb_info *sbi)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct discard_policy dpolicy;
	bool dropped;

	__init_discard_policy(sbi, &dpolicy, DPOLICY_UMOUNT,
					dcc->discard_granularity);
	dpolicy.timeout = UMOUNT_DISCARD_TIMEOUT;
	__issue_discard_cmd(sbi, &dpolicy);
	dropped = __drop_discard_cmd(sbi);

	/* just to make sure there is no pending discard commands */
	__wait_all_discard_cmd(sbi, NULL);

	f2fs_bug_on(sbi, atomic_read(&dcc->discard_cmd_cnt));
	return dropped;
}