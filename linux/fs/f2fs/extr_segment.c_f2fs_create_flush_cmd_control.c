#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct flush_cmd_control {scalar_t__ f2fs_issue_flush; int /*<<< orphan*/  issue_list; int /*<<< orphan*/  flush_wait_queue; int /*<<< orphan*/  queued_flush; int /*<<< orphan*/  issued_flush; } ;
struct f2fs_sb_info {TYPE_2__* sb; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_6__ {struct flush_cmd_control* fcc_info; } ;
struct TYPE_5__ {TYPE_1__* s_bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FLUSH_MERGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (scalar_t__) ; 
 TYPE_3__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct flush_cmd_control* f2fs_kzalloc (struct f2fs_sb_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issue_flush_thread ; 
 scalar_t__ kthread_run (int /*<<< orphan*/ ,struct f2fs_sb_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct flush_cmd_control*) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

int f2fs_create_flush_cmd_control(struct f2fs_sb_info *sbi)
{
	dev_t dev = sbi->sb->s_bdev->bd_dev;
	struct flush_cmd_control *fcc;
	int err = 0;

	if (SM_I(sbi)->fcc_info) {
		fcc = SM_I(sbi)->fcc_info;
		if (fcc->f2fs_issue_flush)
			return err;
		goto init_thread;
	}

	fcc = f2fs_kzalloc(sbi, sizeof(struct flush_cmd_control), GFP_KERNEL);
	if (!fcc)
		return -ENOMEM;
	atomic_set(&fcc->issued_flush, 0);
	atomic_set(&fcc->queued_flush, 0);
	init_waitqueue_head(&fcc->flush_wait_queue);
	init_llist_head(&fcc->issue_list);
	SM_I(sbi)->fcc_info = fcc;
	if (!test_opt(sbi, FLUSH_MERGE))
		return err;

init_thread:
	fcc->f2fs_issue_flush = kthread_run(issue_flush_thread, sbi,
				"f2fs_flush-%u:%u", MAJOR(dev), MINOR(dev));
	if (IS_ERR(fcc->f2fs_issue_flush)) {
		err = PTR_ERR(fcc->f2fs_issue_flush);
		kvfree(fcc);
		SM_I(sbi)->fcc_info = NULL;
		return err;
	}

	return err;
}