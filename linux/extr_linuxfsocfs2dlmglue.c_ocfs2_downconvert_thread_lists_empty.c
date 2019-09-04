#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ocfs2_super {int /*<<< orphan*/  dc_task_lock; int /*<<< orphan*/  blocked_lock_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ocfs2_downconvert_thread_lists_empty(struct ocfs2_super *osb)
{
	int empty = 0;
	unsigned long flags;

	spin_lock_irqsave(&osb->dc_task_lock, flags);
	if (list_empty(&osb->blocked_lock_list))
		empty = 1;

	spin_unlock_irqrestore(&osb->dc_task_lock, flags);
	return empty;
}