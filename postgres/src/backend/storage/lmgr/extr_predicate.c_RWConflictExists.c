#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  outLink; TYPE_1__ const* sxactIn; } ;
struct TYPE_6__ {int /*<<< orphan*/  outConflicts; int /*<<< orphan*/  inConflicts; } ;
typedef  TYPE_1__ SERIALIZABLEXACT ;
typedef  TYPE_2__* RWConflict ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  RWConflictData ; 
 scalar_t__ SHMQueueEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ SHMQueueNext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SxactIsDoomed (TYPE_1__ const*) ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outLink ; 

__attribute__((used)) static bool
RWConflictExists(const SERIALIZABLEXACT *reader, const SERIALIZABLEXACT *writer)
{
	RWConflict	conflict;

	Assert(reader != writer);

	/* Check the ends of the purported conflict first. */
	if (SxactIsDoomed(reader)
		|| SxactIsDoomed(writer)
		|| SHMQueueEmpty(&reader->outConflicts)
		|| SHMQueueEmpty(&writer->inConflicts))
		return false;

	/* A conflict is possible; walk the list to find out. */
	conflict = (RWConflict)
		SHMQueueNext(&reader->outConflicts,
					 &reader->outConflicts,
					 offsetof(RWConflictData, outLink));
	while (conflict)
	{
		if (conflict->sxactIn == writer)
			return true;
		conflict = (RWConflict)
			SHMQueueNext(&reader->outConflicts,
						 &conflict->outLink,
						 offsetof(RWConflictData, outLink));
	}

	/* No conflict found. */
	return false;
}