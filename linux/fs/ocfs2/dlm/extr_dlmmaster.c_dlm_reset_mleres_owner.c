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
struct dlm_master_list_entry {int /*<<< orphan*/  mnamehash; int /*<<< orphan*/  mnamelen; int /*<<< orphan*/  mname; } ;
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  master_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 struct dlm_lock_resource* __dlm_lookup_lockres (struct dlm_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  __dlm_put_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_move_lockres_to_recovery_list (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_set_lockres_owner (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dlm_lock_resource *dlm_reset_mleres_owner(struct dlm_ctxt *dlm,
					struct dlm_master_list_entry *mle)
{
	struct dlm_lock_resource *res;

	/* Find the lockres associated to the mle and set its owner to UNK */
	res = __dlm_lookup_lockres(dlm, mle->mname, mle->mnamelen,
				   mle->mnamehash);
	if (res) {
		spin_unlock(&dlm->master_lock);

		/* move lockres onto recovery list */
		spin_lock(&res->spinlock);
		dlm_set_lockres_owner(dlm, res, DLM_LOCK_RES_OWNER_UNKNOWN);
		dlm_move_lockres_to_recovery_list(dlm, res);
		spin_unlock(&res->spinlock);
		dlm_lockres_put(res);

		/* about to get rid of mle, detach from heartbeat */
		__dlm_mle_detach_hb_events(dlm, mle);

		/* dump the mle */
		spin_lock(&dlm->master_lock);
		__dlm_put_mle(mle);
		spin_unlock(&dlm->master_lock);
	}

	return res;
}