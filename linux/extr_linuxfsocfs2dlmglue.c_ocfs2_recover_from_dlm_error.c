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
struct ocfs2_lock_res {int /*<<< orphan*/  l_event; int /*<<< orphan*/  l_lock; int /*<<< orphan*/  l_unlock_action; int /*<<< orphan*/  l_action; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_AST_INVALID ; 
 int /*<<< orphan*/  OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  OCFS2_LOCK_UPCONVERT_FINISHING ; 
 int /*<<< orphan*/  OCFS2_UNLOCK_INVALID ; 
 int /*<<< orphan*/  lockres_clear_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_recover_from_dlm_error(struct ocfs2_lock_res *lockres,
						int convert)
{
	unsigned long flags;

	spin_lock_irqsave(&lockres->l_lock, flags);
	lockres_clear_flags(lockres, OCFS2_LOCK_BUSY);
	lockres_clear_flags(lockres, OCFS2_LOCK_UPCONVERT_FINISHING);
	if (convert)
		lockres->l_action = OCFS2_AST_INVALID;
	else
		lockres->l_unlock_action = OCFS2_UNLOCK_INVALID;
	spin_unlock_irqrestore(&lockres->l_lock, flags);

	wake_up(&lockres->l_event);
}