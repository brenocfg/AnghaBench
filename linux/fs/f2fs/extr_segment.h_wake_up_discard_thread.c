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
struct discard_cmd_control {int discard_granularity; int discard_wake; int /*<<< orphan*/  discard_wait_queue; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/ * pend_list; } ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISCARD_TIME ; 
 int MAX_PLIST_NUM ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  is_idle (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void wake_up_discard_thread(struct f2fs_sb_info *sbi, bool force)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	bool wakeup = false;
	int i;

	if (force)
		goto wake_up;

	mutex_lock(&dcc->cmd_lock);
	for (i = MAX_PLIST_NUM - 1; i >= 0; i--) {
		if (i + 1 < dcc->discard_granularity)
			break;
		if (!list_empty(&dcc->pend_list[i])) {
			wakeup = true;
			break;
		}
	}
	mutex_unlock(&dcc->cmd_lock);
	if (!wakeup || !is_idle(sbi, DISCARD_TIME))
		return;
wake_up:
	dcc->discard_wake = 1;
	wake_up_interruptible_all(&dcc->discard_wait_queue);
}