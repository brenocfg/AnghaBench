#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TypeName ;
struct TYPE_15__ {scalar_t__ contype; int convalidated; int /*<<< orphan*/  oid; } ;
struct TYPE_14__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_pg_constraint_conbin ; 
 int /*<<< orphan*/  Anum_pg_constraint_conname ; 
 int /*<<< orphan*/  Anum_pg_constraint_conrelid ; 
 int /*<<< orphan*/  Anum_pg_constraint_contypid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ConstraintRelidTypidNameIndexId ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TYPEOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TypeNameToString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  checkDomainOwner (TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_copytuple (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 int /*<<< orphan*/ * makeTypeNameFromNameList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_1__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typenameTypeId (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validateDomainConstraint (int /*<<< orphan*/ ,char*) ; 

ObjectAddress
AlterDomainValidateConstraint(List *names, const char *constrName)
{
	TypeName   *typename;
	Oid			domainoid;
	Relation	typrel;
	Relation	conrel;
	HeapTuple	tup;
	Form_pg_constraint con;
	Form_pg_constraint copy_con;
	char	   *conbin;
	SysScanDesc scan;
	Datum		val;
	bool		isnull;
	HeapTuple	tuple;
	HeapTuple	copyTuple;
	ScanKeyData skey[3];
	ObjectAddress address;

	/* Make a TypeName so we can use standard type lookup machinery */
	typename = makeTypeNameFromNameList(names);
	domainoid = typenameTypeId(NULL, typename);

	/* Look up the domain in the type table */
	typrel = table_open(TypeRelationId, AccessShareLock);

	tup = SearchSysCache1(TYPEOID, ObjectIdGetDatum(domainoid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", domainoid);

	/* Check it's a domain and check user has permission for ALTER DOMAIN */
	checkDomainOwner(tup);

	/*
	 * Find and check the target constraint
	 */
	conrel = table_open(ConstraintRelationId, RowExclusiveLock);

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

	scan = systable_beginscan(conrel, ConstraintRelidTypidNameIndexId, true,
							  NULL, 3, skey);

	/* There can be at most one matching row */
	if (!HeapTupleIsValid(tuple = systable_getnext(scan)))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("constraint \"%s\" of domain \"%s\" does not exist",
						constrName, TypeNameToString(typename))));

	con = (Form_pg_constraint) GETSTRUCT(tuple);
	if (con->contype != CONSTRAINT_CHECK)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("constraint \"%s\" of domain \"%s\" is not a check constraint",
						constrName, TypeNameToString(typename))));

	val = SysCacheGetAttr(CONSTROID, tuple,
						  Anum_pg_constraint_conbin,
						  &isnull);
	if (isnull)
		elog(ERROR, "null conbin for constraint %u",
			 con->oid);
	conbin = TextDatumGetCString(val);

	validateDomainConstraint(domainoid, conbin);

	/*
	 * Now update the catalog, while we have the door open.
	 */
	copyTuple = heap_copytuple(tuple);
	copy_con = (Form_pg_constraint) GETSTRUCT(copyTuple);
	copy_con->convalidated = true;
	CatalogTupleUpdate(conrel, &copyTuple->t_self, copyTuple);

	InvokeObjectPostAlterHook(ConstraintRelationId, con->oid, 0);

	ObjectAddressSet(address, TypeRelationId, domainoid);

	heap_freetuple(copyTuple);

	systable_endscan(scan);

	table_close(typrel, AccessShareLock);
	table_close(conrel, RowExclusiveLock);

	ReleaseSysCache(tup);

	return address;
}