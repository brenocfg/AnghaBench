#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int cycle_ctr; int num_vacuums; int max_vacuums; TYPE_4__* vacuums; } ;
struct TYPE_8__ {scalar_t__ relId; scalar_t__ dbId; } ;
struct TYPE_11__ {int cycleid; TYPE_1__ relid; } ;
struct TYPE_9__ {TYPE_1__ lockRelId; } ;
struct TYPE_10__ {TYPE_2__ rd_lockInfo; } ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__ BTOneVacInfo ;
typedef  int BTCycleId ;

/* Variables and functions */
 int /*<<< orphan*/  BtreeVacuumLock ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MAX_BT_CYCLE_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 TYPE_5__* btvacinfo ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 

BTCycleId
_bt_start_vacuum(Relation rel)
{
	BTCycleId	result;
	int			i;
	BTOneVacInfo *vac;

	LWLockAcquire(BtreeVacuumLock, LW_EXCLUSIVE);

	/*
	 * Assign the next cycle ID, being careful to avoid zero as well as the
	 * reserved high values.
	 */
	result = ++(btvacinfo->cycle_ctr);
	if (result == 0 || result > MAX_BT_CYCLE_ID)
		result = btvacinfo->cycle_ctr = 1;

	/* Let's just make sure there's no entry already for this index */
	for (i = 0; i < btvacinfo->num_vacuums; i++)
	{
		vac = &btvacinfo->vacuums[i];
		if (vac->relid.relId == rel->rd_lockInfo.lockRelId.relId &&
			vac->relid.dbId == rel->rd_lockInfo.lockRelId.dbId)
		{
			/*
			 * Unlike most places in the backend, we have to explicitly
			 * release our LWLock before throwing an error.  This is because
			 * we expect _bt_end_vacuum() to be called before transaction
			 * abort cleanup can run to release LWLocks.
			 */
			LWLockRelease(BtreeVacuumLock);
			elog(ERROR, "multiple active vacuums for index \"%s\"",
				 RelationGetRelationName(rel));
		}
	}

	/* OK, add an entry */
	if (btvacinfo->num_vacuums >= btvacinfo->max_vacuums)
	{
		LWLockRelease(BtreeVacuumLock);
		elog(ERROR, "out of btvacinfo slots");
	}
	vac = &btvacinfo->vacuums[btvacinfo->num_vacuums];
	vac->relid = rel->rd_lockInfo.lockRelId;
	vac->cycleid = result;
	btvacinfo->num_vacuums++;

	LWLockRelease(BtreeVacuumLock);
	return result;
}