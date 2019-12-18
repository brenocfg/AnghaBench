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
struct ocfs2_lock_res {int l_flags; unsigned int l_pending_gen; int /*<<< orphan*/  l_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OCFS2_LOCK_BUSY ; 
 int /*<<< orphan*/  OCFS2_LOCK_PENDING ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockres_or_flags (struct ocfs2_lock_res*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int lockres_set_pending(struct ocfs2_lock_res *lockres)
{
	assert_spin_locked(&lockres->l_lock);
	BUG_ON(!(lockres->l_flags & OCFS2_LOCK_BUSY));

	lockres_or_flags(lockres, OCFS2_LOCK_PENDING);

	return lockres->l_pending_gen;
}