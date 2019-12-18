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
struct dlm_master_list_entry {int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  woken; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  __dlm_unlink_mle (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_clean_migration_mle(struct dlm_ctxt *dlm,
				    struct dlm_master_list_entry *mle)
{
	__dlm_mle_detach_hb_events(dlm, mle);

	spin_lock(&mle->spinlock);
	__dlm_unlink_mle(dlm, mle);
	atomic_set(&mle->woken, 1);
	spin_unlock(&mle->spinlock);

	wake_up(&mle->wq);
}