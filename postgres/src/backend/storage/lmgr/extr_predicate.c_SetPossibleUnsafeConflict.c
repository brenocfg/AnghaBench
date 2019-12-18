#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  availableList; } ;
struct TYPE_8__ {int /*<<< orphan*/  inLink; int /*<<< orphan*/  outLink; TYPE_1__* sxactIn; TYPE_1__* sxactOut; } ;
struct TYPE_7__ {int /*<<< orphan*/  possibleUnsafeConflicts; } ;
typedef  TYPE_1__ SERIALIZABLEXACT ;
typedef  TYPE_2__* RWConflict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RWConflictData ; 
 TYPE_6__* RWConflictPool ; 
 int /*<<< orphan*/  SHMQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHMQueueInsertBefore (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SxactIsReadOnly (TYPE_1__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outLink ; 

__attribute__((used)) static void
SetPossibleUnsafeConflict(SERIALIZABLEXACT *roXact,
						  SERIALIZABLEXACT *activeXact)
{
	RWConflict	conflict;

	Assert(roXact != activeXact);
	Assert(SxactIsReadOnly(roXact));
	Assert(!SxactIsReadOnly(activeXact));

	conflict = (RWConflict)
		SHMQueueNext(&RWConflictPool->availableList,
					 &RWConflictPool->availableList,
					 offsetof(RWConflictData, outLink));
	if (!conflict)
		ereport(ERROR,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("not enough elements in RWConflictPool to record a potential read/write conflict"),
				 errhint("You might need to run fewer transactions at a time or increase max_connections.")));

	SHMQueueDelete(&conflict->outLink);

	conflict->sxactOut = activeXact;
	conflict->sxactIn = roXact;
	SHMQueueInsertBefore(&activeXact->possibleUnsafeConflicts,
						 &conflict->outLink);
	SHMQueueInsertBefore(&roXact->possibleUnsafeConflicts,
						 &conflict->inLink);
}