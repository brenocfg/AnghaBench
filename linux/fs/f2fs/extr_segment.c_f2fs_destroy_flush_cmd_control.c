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
struct task_struct {int dummy; } ;
struct flush_cmd_control {struct task_struct* f2fs_issue_flush; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {struct flush_cmd_control* fcc_info; } ;

/* Variables and functions */
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  kvfree (struct flush_cmd_control*) ; 

void f2fs_destroy_flush_cmd_control(struct f2fs_sb_info *sbi, bool free)
{
	struct flush_cmd_control *fcc = SM_I(sbi)->fcc_info;

	if (fcc && fcc->f2fs_issue_flush) {
		struct task_struct *flush_thread = fcc->f2fs_issue_flush;

		fcc->f2fs_issue_flush = NULL;
		kthread_stop(flush_thread);
	}
	if (free) {
		kvfree(fcc);
		SM_I(sbi)->fcc_info = NULL;
	}
}