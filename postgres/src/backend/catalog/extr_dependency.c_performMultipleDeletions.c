#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numrefs; int /*<<< orphan*/ * refs; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  DropBehavior ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireDeletionLock (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  DEPFLAG_ORIGINAL ; 
 int /*<<< orphan*/  DependRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  deleteObjectsInList (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  findDependentObjects (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_object_addresses (TYPE_1__*) ; 
 TYPE_1__* new_object_addresses () ; 
 int /*<<< orphan*/  reportDependentObjects (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
performMultipleDeletions(const ObjectAddresses *objects,
						 DropBehavior behavior, int flags)
{
	Relation	depRel;
	ObjectAddresses *targetObjects;
	int			i;

	/* No work if no objects... */
	if (objects->numrefs <= 0)
		return;

	/*
	 * We save some cycles by opening pg_depend just once and passing the
	 * Relation pointer down to all the recursive deletion steps.
	 */
	depRel = table_open(DependRelationId, RowExclusiveLock);

	/*
	 * Construct a list of objects to delete (ie, the given objects plus
	 * everything directly or indirectly dependent on them).  Note that
	 * because we pass the whole objects list as pendingObjects context, we
	 * won't get a failure from trying to delete an object that is internally
	 * dependent on another one in the list; we'll just skip that object and
	 * delete it when we reach its owner.
	 */
	targetObjects = new_object_addresses();

	for (i = 0; i < objects->numrefs; i++)
	{
		const ObjectAddress *thisobj = objects->refs + i;

		/*
		 * Acquire deletion lock on each target object.  (Ideally the caller
		 * has done this already, but many places are sloppy about it.)
		 */
		AcquireDeletionLock(thisobj, flags);

		findDependentObjects(thisobj,
							 DEPFLAG_ORIGINAL,
							 flags,
							 NULL,	/* empty stack */
							 targetObjects,
							 objects,
							 &depRel);
	}

	/*
	 * Check if deletion is allowed, and report about cascaded deletes.
	 *
	 * If there's exactly one object being deleted, report it the same way as
	 * in performDeletion(), else we have to be vaguer.
	 */
	reportDependentObjects(targetObjects,
						   behavior,
						   flags,
						   (objects->numrefs == 1 ? objects->refs : NULL));

	/* do the deed */
	deleteObjectsInList(targetObjects, &depRel, flags);

	/* And clean up */
	free_object_addresses(targetObjects);

	table_close(depRel, RowExclusiveLock);
}