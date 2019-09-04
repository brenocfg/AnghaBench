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
struct ocfs2_mask_waiter {int dummy; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int __lockres_remove_mask_waiter (struct ocfs2_lock_res*,struct ocfs2_mask_waiter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int lockres_remove_mask_waiter(struct ocfs2_lock_res *lockres,
				      struct ocfs2_mask_waiter *mw)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&lockres->l_lock, flags);
	ret = __lockres_remove_mask_waiter(lockres, mw);
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	return ret;

}