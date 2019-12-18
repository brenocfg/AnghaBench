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
struct dlm_master_list_entry {struct dlm_ctxt* dlm; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  master_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_put_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_put_mle(struct dlm_master_list_entry *mle)
{
	struct dlm_ctxt *dlm;
	dlm = mle->dlm;

	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);
	__dlm_put_mle(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);
}