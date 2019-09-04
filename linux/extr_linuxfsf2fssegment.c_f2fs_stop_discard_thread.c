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
struct f2fs_sb_info {int dummy; } ;
struct discard_cmd_control {struct task_struct* f2fs_issue_discard; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 

void f2fs_stop_discard_thread(struct f2fs_sb_info *sbi)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;

	if (dcc && dcc->f2fs_issue_discard) {
		struct task_struct *discard_thread = dcc->f2fs_issue_discard;

		dcc->f2fs_issue_discard = NULL;
		kthread_stop(discard_thread);
	}
}