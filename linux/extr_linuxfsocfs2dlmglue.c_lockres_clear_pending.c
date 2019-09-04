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
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lockres_clear_pending (struct ocfs2_lock_res*,unsigned int,struct ocfs2_super*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lockres_clear_pending(struct ocfs2_lock_res *lockres,
				  unsigned int generation,
				  struct ocfs2_super *osb)
{
	unsigned long flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	__lockres_clear_pending(lockres, generation, osb);
	spin_unlock_irqrestore(&lockres->l_lock, flags);
}