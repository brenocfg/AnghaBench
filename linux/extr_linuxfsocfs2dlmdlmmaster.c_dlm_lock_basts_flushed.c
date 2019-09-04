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
struct dlm_lock {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  bast_pending; int /*<<< orphan*/  bast_list; } ;
struct dlm_ctxt {int /*<<< orphan*/  ast_lock; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_lock_basts_flushed(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	int ret;
	spin_lock(&dlm->ast_lock);
	spin_lock(&lock->spinlock);
	ret = (list_empty(&lock->bast_list) && !lock->bast_pending);
	spin_unlock(&lock->spinlock);
	spin_unlock(&dlm->ast_lock);
	return ret;
}