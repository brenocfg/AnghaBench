#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sxactIn; TYPE_1__* sxactOut; int /*<<< orphan*/  inLink; } ;
struct TYPE_7__ {int /*<<< orphan*/  possibleUnsafeConflicts; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ SERIALIZABLEXACT ;
typedef  TYPE_2__* RWConflict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  RWConflictData ; 
 int /*<<< orphan*/  ReleaseRWConflict (TYPE_2__*) ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SXACT_FLAG_RO_UNSAFE ; 
 int /*<<< orphan*/  SxactIsROSafe (TYPE_1__*) ; 
 int SxactIsReadOnly (TYPE_1__*) ; 
 int /*<<< orphan*/  inLink ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FlagSxactUnsafe(SERIALIZABLEXACT *sxact)
{
	RWConflict	conflict,
				nextConflict;

	Assert(SxactIsReadOnly(sxact));
	Assert(!SxactIsROSafe(sxact));

	sxact->flags |= SXACT_FLAG_RO_UNSAFE;

	/*
	 * We know this isn't a safe snapshot, so we can stop looking for other
	 * potential conflicts.
	 */
	conflict = (RWConflict)
		SHMQueueNext(&sxact->possibleUnsafeConflicts,
					 &sxact->possibleUnsafeConflicts,
					 offsetof(RWConflictData, inLink));
	while (conflict)
	{
		nextConflict = (RWConflict)
			SHMQueueNext(&sxact->possibleUnsafeConflicts,
						 &conflict->inLink,
						 offsetof(RWConflictData, inLink));

		Assert(!SxactIsReadOnly(conflict->sxactOut));
		Assert(sxact == conflict->sxactIn);

		ReleaseRWConflict(conflict);

		conflict = nextConflict;
	}
}