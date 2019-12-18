#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_1__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ O2NM_MAX_NODES ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ dlm_is_lockres_migratable (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int dlm_migrate_lockres (struct dlm_ctxt*,struct dlm_lock_resource*,scalar_t__) ; 
 scalar_t__ dlm_pick_migration_target (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_empty_lockres(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	int ret;
	int lock_dropped = 0;
	u8 target = O2NM_MAX_NODES;

	assert_spin_locked(&dlm->spinlock);

	spin_lock(&res->spinlock);
	if (dlm_is_lockres_migratable(dlm, res))
		target = dlm_pick_migration_target(dlm, res);
	spin_unlock(&res->spinlock);

	if (target == O2NM_MAX_NODES)
		goto leave;

	/* Wheee! Migrate lockres here! Will sleep so drop spinlock. */
	spin_unlock(&dlm->spinlock);
	lock_dropped = 1;
	ret = dlm_migrate_lockres(dlm, res, target);
	if (ret)
		mlog(0, "%s: res %.*s, Migrate to node %u failed with %d\n",
		     dlm->name, res->lockname.len, res->lockname.name,
		     target, ret);
	spin_lock(&dlm->spinlock);
leave:
	return lock_dropped;
}