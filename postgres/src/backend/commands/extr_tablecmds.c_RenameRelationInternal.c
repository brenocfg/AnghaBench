#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  relname; } ;
struct TYPE_18__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_17__ {TYPE_1__* rd_rel; } ;
struct TYPE_16__ {scalar_t__ relkind; int /*<<< orphan*/  reltype; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__* HeapTuple ;
typedef  TYPE_4__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_3__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_3__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHookArg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetNamespace (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RenameConstraintById (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  RenameTypeInternal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_3__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  get_index_constraint (int /*<<< orphan*/ ) ; 
 scalar_t__ get_relname_relid (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_3__*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RenameRelationInternal(Oid myrelid, const char *newrelname, bool is_internal, bool is_index)
{
	Relation	targetrelation;
	Relation	relrelation;	/* for RELATION relation */
	HeapTuple	reltup;
	Form_pg_class relform;
	Oid			namespaceId;

	/*
	 * Grab a lock on the target relation, which we will NOT release until end
	 * of transaction.  We need at least a self-exclusive lock so that
	 * concurrent DDL doesn't overwrite the rename if they start updating
	 * while still seeing the old version.  The lock also guards against
	 * triggering relcache reloads in concurrent sessions, which might not
	 * handle this information changing under them.  For indexes, we can use a
	 * reduced lock level because RelationReloadIndexInfo() handles indexes
	 * specially.
	 */
	targetrelation = relation_open(myrelid, is_index ? ShareUpdateExclusiveLock : AccessExclusiveLock);
	namespaceId = RelationGetNamespace(targetrelation);

	/*
	 * Find relation's pg_class tuple, and make sure newrelname isn't in use.
	 */
	relrelation = table_open(RelationRelationId, RowExclusiveLock);

	reltup = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(myrelid));
	if (!HeapTupleIsValid(reltup))	/* shouldn't happen */
		elog(ERROR, "cache lookup failed for relation %u", myrelid);
	relform = (Form_pg_class) GETSTRUCT(reltup);

	if (get_relname_relid(newrelname, namespaceId) != InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_TABLE),
				 errmsg("relation \"%s\" already exists",
						newrelname)));

	/*
	 * Update pg_class tuple with new relname.  (Scribbling on reltup is OK
	 * because it's a copy...)
	 */
	namestrcpy(&(relform->relname), newrelname);

	CatalogTupleUpdate(relrelation, &reltup->t_self, reltup);

	InvokeObjectPostAlterHookArg(RelationRelationId, myrelid, 0,
								 InvalidOid, is_internal);

	heap_freetuple(reltup);
	table_close(relrelation, RowExclusiveLock);

	/*
	 * Also rename the associated type, if any.
	 */
	if (OidIsValid(targetrelation->rd_rel->reltype))
		RenameTypeInternal(targetrelation->rd_rel->reltype,
						   newrelname, namespaceId);

	/*
	 * Also rename the associated constraint, if any.
	 */
	if (targetrelation->rd_rel->relkind == RELKIND_INDEX ||
		targetrelation->rd_rel->relkind == RELKIND_PARTITIONED_INDEX)
	{
		Oid			constraintId = get_index_constraint(myrelid);

		if (OidIsValid(constraintId))
			RenameConstraintById(constraintId, newrelname);
	}

	/*
	 * Close rel, but keep lock!
	 */
	relation_close(targetrelation, NoLock);
}