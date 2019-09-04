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
struct dlm_master_list_entry {int /*<<< orphan*/  mle_refs; int /*<<< orphan*/  inuse; struct dlm_ctxt* dlm; } ;
struct dlm_ctxt {int /*<<< orphan*/  master_lock; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_get_mle_inuse(struct dlm_master_list_entry *mle)
{
	struct dlm_ctxt *dlm;
	dlm = mle->dlm;

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&dlm->master_lock);
	mle->inuse++;
	kref_get(&mle->mle_refs);
}