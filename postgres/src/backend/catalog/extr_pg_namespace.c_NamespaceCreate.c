#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_9__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_8__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  scalar_t__ Datum ;
typedef  char const Acl ;

/* Variables and functions */
 int Anum_pg_namespace_nspacl ; 
 int Anum_pg_namespace_nspname ; 
 int Anum_pg_namespace_nspowner ; 
 int Anum_pg_namespace_oid ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_SCHEMA ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAMESPACENAME ; 
 scalar_t__ NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NamespaceOidIndexId ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int Natts_pg_namespace ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 scalar_t__ ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PointerGetDatum (char const*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 scalar_t__ SearchSysCacheExists1 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char* get_user_default_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_2__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnNewAcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
NamespaceCreate(const char *nspName, Oid ownerId, bool isTemp)
{
	Relation	nspdesc;
	HeapTuple	tup;
	Oid			nspoid;
	bool		nulls[Natts_pg_namespace];
	Datum		values[Natts_pg_namespace];
	NameData	nname;
	TupleDesc	tupDesc;
	ObjectAddress myself;
	int			i;
	Acl		   *nspacl;

	/* sanity checks */
	if (!nspName)
		elog(ERROR, "no namespace name supplied");

	/* make sure there is no existing namespace of same name */
	if (SearchSysCacheExists1(NAMESPACENAME, PointerGetDatum(nspName)))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_SCHEMA),
				 errmsg("schema \"%s\" already exists", nspName)));

	if (!isTemp)
		nspacl = get_user_default_acl(OBJECT_SCHEMA, ownerId,
									  InvalidOid);
	else
		nspacl = NULL;

	nspdesc = table_open(NamespaceRelationId, RowExclusiveLock);
	tupDesc = nspdesc->rd_att;

	/* initialize nulls and values */
	for (i = 0; i < Natts_pg_namespace; i++)
	{
		nulls[i] = false;
		values[i] = (Datum) NULL;
	}

	nspoid = GetNewOidWithIndex(nspdesc, NamespaceOidIndexId,
								Anum_pg_namespace_oid);
	values[Anum_pg_namespace_oid - 1] = ObjectIdGetDatum(nspoid);
	namestrcpy(&nname, nspName);
	values[Anum_pg_namespace_nspname - 1] = NameGetDatum(&nname);
	values[Anum_pg_namespace_nspowner - 1] = ObjectIdGetDatum(ownerId);
	if (nspacl != NULL)
		values[Anum_pg_namespace_nspacl - 1] = PointerGetDatum(nspacl);
	else
		nulls[Anum_pg_namespace_nspacl - 1] = true;


	tup = heap_form_tuple(tupDesc, values, nulls);

	CatalogTupleInsert(nspdesc, tup);
	Assert(OidIsValid(nspoid));

	table_close(nspdesc, RowExclusiveLock);

	/* Record dependencies */
	myself.classId = NamespaceRelationId;
	myself.objectId = nspoid;
	myself.objectSubId = 0;

	/* dependency on owner */
	recordDependencyOnOwner(NamespaceRelationId, nspoid, ownerId);

	/* dependences on roles mentioned in default ACL */
	recordDependencyOnNewAcl(NamespaceRelationId, nspoid, 0, ownerId, nspacl);

	/* dependency on extension ... but not for magic temp schemas */
	if (!isTemp)
		recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new schema */
	InvokeObjectPostCreateHook(NamespaceRelationId, nspoid, 0);

	return nspoid;
}