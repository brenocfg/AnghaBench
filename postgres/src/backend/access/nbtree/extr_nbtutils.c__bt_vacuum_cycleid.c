#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int num_vacuums; TYPE_5__* vacuums; } ;
struct TYPE_8__ {scalar_t__ relId; scalar_t__ dbId; } ;
struct TYPE_12__ {int /*<<< orphan*/  cycleid; TYPE_1__ relid; } ;
struct TYPE_9__ {scalar_t__ relId; scalar_t__ dbId; } ;
struct TYPE_10__ {TYPE_2__ lockRelId; } ;
struct TYPE_11__ {TYPE_3__ rd_lockInfo; } ;
typedef  TYPE_4__* Relation ;
typedef  TYPE_5__ BTOneVacInfo ;
typedef  int /*<<< orphan*/  BTCycleId ;

/* Variables and functions */
 int /*<<< orphan*/  BtreeVacuumLock ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 TYPE_6__* btvacinfo ; 

BTCycleId
_bt_vacuum_cycleid(Relation rel)
{
	BTCycleId	result = 0;
	int			i;

	/* Share lock is enough since this is a read-only operation */
	LWLockAcquire(BtreeVacuumLock, LW_SHARED);

	for (i = 0; i < btvacinfo->num_vacuums; i++)
	{
		BTOneVacInfo *vac = &btvacinfo->vacuums[i];

		if (vac->relid.relId == rel->rd_lockInfo.lockRelId.relId &&
			vac->relid.dbId == rel->rd_lockInfo.lockRelId.dbId)
		{
			result = vac->cycleid;
			break;
		}
	}

	LWLockRelease(BtreeVacuumLock);
	return result;
}