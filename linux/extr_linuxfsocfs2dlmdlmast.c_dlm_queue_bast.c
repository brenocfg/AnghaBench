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
struct dlm_lock {int dummy; } ;
struct dlm_ctxt {int /*<<< orphan*/  ast_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __dlm_queue_bast (struct dlm_ctxt*,struct dlm_lock*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dlm_queue_bast(struct dlm_ctxt *dlm, struct dlm_lock *lock)
{
	BUG_ON(!dlm);
	BUG_ON(!lock);

	spin_lock(&dlm->ast_lock);
	__dlm_queue_bast(dlm, lock);
	spin_unlock(&dlm->ast_lock);
}