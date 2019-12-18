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
struct discard_cmd_control {int dummy; } ;
struct discard_cmd {int error; int /*<<< orphan*/  len; int /*<<< orphan*/  start; int /*<<< orphan*/  lstart; int /*<<< orphan*/  ref; int /*<<< orphan*/  lock; scalar_t__ bio_ref; int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KERN_INFO ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __detach_discard_cmd (struct discard_cmd_control*,struct discard_cmd*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_f2fs_remove_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __remove_discard_cmd(struct f2fs_sb_info *sbi,
							struct discard_cmd *dc)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	unsigned long flags;

	trace_f2fs_remove_discard(dc->bdev, dc->start, dc->len);

	spin_lock_irqsave(&dc->lock, flags);
	if (dc->bio_ref) {
		spin_unlock_irqrestore(&dc->lock, flags);
		return;
	}
	spin_unlock_irqrestore(&dc->lock, flags);

	f2fs_bug_on(sbi, dc->ref);

	if (dc->error == -EOPNOTSUPP)
		dc->error = 0;

	if (dc->error)
		printk_ratelimited(
			"%sF2FS-fs: Issue discard(%u, %u, %u) failed, ret: %d",
			KERN_INFO, dc->lstart, dc->start, dc->len, dc->error);
	__detach_discard_cmd(dcc, dc);
}