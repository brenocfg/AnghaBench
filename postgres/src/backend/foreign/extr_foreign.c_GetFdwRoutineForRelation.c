#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rd_fdwroutine; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  FdwRoutine ;

/* Variables and functions */
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/ * GetFdwRoutineByRelId (int /*<<< orphan*/ ) ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ palloc (int) ; 

FdwRoutine *
GetFdwRoutineForRelation(Relation relation, bool makecopy)
{
	FdwRoutine *fdwroutine;
	FdwRoutine *cfdwroutine;

	if (relation->rd_fdwroutine == NULL)
	{
		/* Get the info by consulting the catalogs and the FDW code */
		fdwroutine = GetFdwRoutineByRelId(RelationGetRelid(relation));

		/* Save the data for later reuse in CacheMemoryContext */
		cfdwroutine = (FdwRoutine *) MemoryContextAlloc(CacheMemoryContext,
														sizeof(FdwRoutine));
		memcpy(cfdwroutine, fdwroutine, sizeof(FdwRoutine));
		relation->rd_fdwroutine = cfdwroutine;

		/* Give back the locally palloc'd copy regardless of makecopy */
		return fdwroutine;
	}

	/* We have valid cached data --- does the caller want a copy? */
	if (makecopy)
	{
		fdwroutine = (FdwRoutine *) palloc(sizeof(FdwRoutine));
		memcpy(fdwroutine, relation->rd_fdwroutine, sizeof(FdwRoutine));
		return fdwroutine;
	}

	/* Only a short-lived reference is needed, so just hand back cached copy */
	return relation->rd_fdwroutine;
}