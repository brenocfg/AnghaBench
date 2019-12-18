#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  DropBehavior ;

/* Variables and functions */
 int /*<<< orphan*/  AcquireDeletionLock (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPFLAG_ORIGINAL ; 
 int /*<<< orphan*/  DependRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  deleteObjectsInList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  findDependentObjects (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_object_addresses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_object_addresses () ; 
 int /*<<< orphan*/  reportDependentObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
performDeletion(const ObjectAddress *object,
				DropBehavior behavior, int flags)
{
	Relation	depRel;
	ObjectAddresses *targetObjects;

	/*
	 * We save some cycles by opening pg_depend just once and passing the
	 * Relation pointer down to all the recursive deletion steps.
	 */
	depRel = table_open(DependRelationId, RowExclusiveLock);

	/*
	 * Acquire deletion lock on the target object.  (Ideally the caller has
	 * done this already, but many places are sloppy about it.)
	 */
	AcquireDeletionLock(object, 0);

	/*
	 * Construct a list of objects to delete (ie, the given object plus
	 * everything directly or indirectly dependent on it).
	 */
	targetObjects = new_object_addresses();

	findDependentObjects(object,
						 DEPFLAG_ORIGINAL,
						 flags,
						 NULL,	/* empty stack */
						 targetObjects,
						 NULL,	/* no pendingObjects */
						 &depRel);

	/*
	 * Check if deletion is allowed, and report about cascaded deletes.
	 */
	reportDependentObjects(targetObjects,
						   behavior,
						   flags,
						   object);

	/* do the deed */
	deleteObjectsInList(targetObjects, &depRel, flags);

	/* And clean up */
	free_object_addresses(targetObjects);

	table_close(depRel, RowExclusiveLock);
}