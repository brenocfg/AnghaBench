#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_9__ {scalar_t__ objectSubId; int /*<<< orphan*/  classId; int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_depend_classid ; 
 int /*<<< orphan*/  Anum_pg_depend_objid ; 
 int /*<<< orphan*/  Anum_pg_depend_objsubid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DeleteComments (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DeleteInitPrivs (TYPE_1__ const*) ; 
 int /*<<< orphan*/  DeleteSecurityLabel (TYPE_1__ const*) ; 
 int /*<<< orphan*/  DependDependerIndexId ; 
 int /*<<< orphan*/  DependRelationId ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  Int32GetDatum (scalar_t__) ; 
 int /*<<< orphan*/  InvokeObjectDropHookArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int PERFORM_DELETION_CONCURRENTLY ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deleteSharedDependencyRecordsFor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  doDeletion (TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deleteOneObject(const ObjectAddress *object, Relation *depRel, int flags)
{
	ScanKeyData key[3];
	int			nkeys;
	SysScanDesc scan;
	HeapTuple	tup;

	/* DROP hook of the objects being removed */
	InvokeObjectDropHookArg(object->classId, object->objectId,
							object->objectSubId, flags);

	/*
	 * Close depRel if we are doing a drop concurrently.  The object deletion
	 * subroutine will commit the current transaction, so we can't keep the
	 * relation open across doDeletion().
	 */
	if (flags & PERFORM_DELETION_CONCURRENTLY)
		table_close(*depRel, RowExclusiveLock);

	/*
	 * Delete the object itself, in an object-type-dependent way.
	 *
	 * We used to do this after removing the outgoing dependency links, but it
	 * seems just as reasonable to do it beforehand.  In the concurrent case
	 * we *must* do it in this order, because we can't make any transactional
	 * updates before calling doDeletion() --- they'd get committed right
	 * away, which is not cool if the deletion then fails.
	 */
	doDeletion(object, flags);

	/*
	 * Reopen depRel if we closed it above
	 */
	if (flags & PERFORM_DELETION_CONCURRENTLY)
		*depRel = table_open(DependRelationId, RowExclusiveLock);

	/*
	 * Now remove any pg_depend records that link from this object to others.
	 * (Any records linking to this object should be gone already.)
	 *
	 * When dropping a whole object (subId = 0), remove all pg_depend records
	 * for its sub-objects too.
	 */
	ScanKeyInit(&key[0],
				Anum_pg_depend_classid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->classId));
	ScanKeyInit(&key[1],
				Anum_pg_depend_objid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(object->objectId));
	if (object->objectSubId != 0)
	{
		ScanKeyInit(&key[2],
					Anum_pg_depend_objsubid,
					BTEqualStrategyNumber, F_INT4EQ,
					Int32GetDatum(object->objectSubId));
		nkeys = 3;
	}
	else
		nkeys = 2;

	scan = systable_beginscan(*depRel, DependDependerIndexId, true,
							  NULL, nkeys, key);

	while (HeapTupleIsValid(tup = systable_getnext(scan)))
	{
		CatalogTupleDelete(*depRel, &tup->t_self);
	}

	systable_endscan(scan);

	/*
	 * Delete shared dependency references related to this object.  Again, if
	 * subId = 0, remove records for sub-objects too.
	 */
	deleteSharedDependencyRecordsFor(object->classId, object->objectId,
									 object->objectSubId);


	/*
	 * Delete any comments, security labels, or initial privileges associated
	 * with this object.  (This is a convenient place to do these things,
	 * rather than having every object type know to do it.)
	 */
	DeleteComments(object->objectId, object->classId, object->objectSubId);
	DeleteSecurityLabel(object);
	DeleteInitPrivs(object);

	/*
	 * CommandCounterIncrement here to ensure that preceding changes are all
	 * visible to the next deletion step.
	 */
	CommandCounterIncrement();

	/*
	 * And we're done!
	 */
}