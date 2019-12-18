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
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_7__ {int /*<<< orphan*/  oid; } ;
struct TYPE_6__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  DropBehavior ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_constraint_conname ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  Anum_pg_constraint_contypid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CacheInvalidateHeapTuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPEOID ; 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  checkDomainOwner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  performDeletion (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typenameTypeId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ObjectAddress
AlterDomainDropConstraint(List *names, const char *constrName,
						  DropBehavior behavior, bool missing_ok)
{
	TypeName   *typename;
	Oid			domainoid;
	HeapTuple	tup;
	Relation	rel;
	Relation	conrel;
	SysScanDesc conscan;
	ScanKeyData skey[3];
	HeapTuple	contup;
	bool		found = false;
	ObjectAddress address;

	/* Make a TypeName so we can use standard type lookup machinery */
	typename = makeTypeNameFromNameList(names);
	domainoid = typenameTypeId(NULL, typename);

	/* Look up the domain in the type table */
	rel = table_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy1(TYPEOID, ObjectIdGetDatum(domainoid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", domainoid);

	/* Check it's a domain and check user has permission for ALTER DOMAIN */
	checkDomainOwner(tup);

	/* Grab an appropriate lock on the pg_constraint relation */
	conrel = table_open(ConstraintRelationId, RowExclusiveLock);

	/* Find and remove the target constraint */
	ScanKeyInit(&skey[0],
				Anum_pg_constraint_conrelid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(InvalidOid));
	ScanKeyInit(&skey[1],
				Anum_pg_constraint_contypid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(domainoid));
	ScanKeyInit(&skey[2],
				Anum_pg_constraint_conname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(constrName));

	conscan = systable_beginscan(conrel, ConstraintRelidTypidNameIndexId, true,
								 NULL, 3, skey);

	/* There can be at most one matching row */
	if ((contup = systable_getnext(conscan)) != NULL)
	{
		ObjectAddress conobj;

		conobj.classId = ConstraintRelationId;
		conobj.objectId = ((Form_pg_constraint) GETSTRUCT(contup))->oid;
		conobj.objectSubId = 0;

		performDeletion(&conobj, behavior, 0);
		found = true;
	}

	/* Clean up after the scan */
	systable_endscan(conscan);
	table_close(conrel, RowExclusiveLock);

	if (!found)
	{
		if (!missing_ok)
			ereport(ERROR,
					(errcode(ERRCODE_UNDEFINED_OBJECT),
					 errmsg("constraint \"%s\" of domain \"%s\" does not exist",
							constrName, TypeNameToString(typename))));
		else
			ereport(NOTICE,
					(errmsg("constraint \"%s\" of domain \"%s\" does not exist, skipping",
							constrName, TypeNameToString(typename))));
	}

	/*
	 * We must send out an sinval message for the domain, to ensure that any
	 * dependent plans get rebuilt.  Since this command doesn't change the
	 * domain's pg_type row, that won't happen automatically; do it manually.
	 */
	CacheInvalidateHeapTuple(rel, tup, NULL);

	ObjectAddressSet(address, TypeRelationId, domainoid);

	/* Clean up */
	table_close(rel, RowExclusiveLock);

	return address;
}