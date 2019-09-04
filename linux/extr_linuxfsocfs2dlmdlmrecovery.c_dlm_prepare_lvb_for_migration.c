#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dlm_migratable_lockres {int /*<<< orphan*/  lvb; } ;
struct TYPE_7__ {scalar_t__ type; int /*<<< orphan*/  node; int /*<<< orphan*/  cookie; } ;
struct dlm_lock {TYPE_4__* lockres; TYPE_3__ ml; TYPE_1__* lksb; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_2__ lockname; } ;
struct TYPE_5__ {int /*<<< orphan*/  lvb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DLM_BLOCKED_LIST ; 
 int /*<<< orphan*/  DLM_LVB_LEN ; 
 scalar_t__ LKM_EXMODE ; 
 scalar_t__ LKM_PRMODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_lock_cookie_seq (int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_lvb_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (TYPE_4__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_prepare_lvb_for_migration(struct dlm_lock *lock,
					  struct dlm_migratable_lockres *mres,
					  int queue)
{
	if (!lock->lksb)
	       return;

	/* Ignore lvb in all locks in the blocked list */
	if (queue == DLM_BLOCKED_LIST)
		return;

	/* Only consider lvbs in locks with granted EX or PR lock levels */
	if (lock->ml.type != LKM_EXMODE && lock->ml.type != LKM_PRMODE)
		return;

	if (dlm_lvb_is_empty(mres->lvb)) {
		memcpy(mres->lvb, lock->lksb->lvb, DLM_LVB_LEN);
		return;
	}

	/* Ensure the lvb copied for migration matches in other valid locks */
	if (!memcmp(mres->lvb, lock->lksb->lvb, DLM_LVB_LEN))
		return;

	mlog(ML_ERROR, "Mismatched lvb in lock cookie=%u:%llu, name=%.*s, "
	     "node=%u\n",
	     dlm_get_lock_cookie_node(be64_to_cpu(lock->ml.cookie)),
	     dlm_get_lock_cookie_seq(be64_to_cpu(lock->ml.cookie)),
	     lock->lockres->lockname.len, lock->lockres->lockname.name,
	     lock->ml.node);
	dlm_print_one_lock_resource(lock->lockres);
	BUG();
}