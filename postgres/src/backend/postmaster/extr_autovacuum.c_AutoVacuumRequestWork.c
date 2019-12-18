#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* av_workItems; } ;
struct TYPE_3__ {int avw_used; int avw_active; int /*<<< orphan*/  avw_blockNumber; int /*<<< orphan*/  avw_relation; int /*<<< orphan*/  avw_database; int /*<<< orphan*/  avw_type; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  int /*<<< orphan*/  AutoVacuumWorkItemType ;
typedef  TYPE_1__ AutoVacuumWorkItem ;

/* Variables and functions */
 TYPE_2__* AutoVacuumShmem ; 
 int /*<<< orphan*/  AutovacuumLock ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int NUM_WORKITEMS ; 

bool
AutoVacuumRequestWork(AutoVacuumWorkItemType type, Oid relationId,
					  BlockNumber blkno)
{
	int			i;
	bool		result = false;

	LWLockAcquire(AutovacuumLock, LW_EXCLUSIVE);

	/*
	 * Locate an unused work item and fill it with the given data.
	 */
	for (i = 0; i < NUM_WORKITEMS; i++)
	{
		AutoVacuumWorkItem *workitem = &AutoVacuumShmem->av_workItems[i];

		if (workitem->avw_used)
			continue;

		workitem->avw_used = true;
		workitem->avw_active = false;
		workitem->avw_type = type;
		workitem->avw_database = MyDatabaseId;
		workitem->avw_relation = relationId;
		workitem->avw_blockNumber = blkno;
		result = true;

		/* done */
		break;
	}

	LWLockRelease(AutovacuumLock);

	return result;
}