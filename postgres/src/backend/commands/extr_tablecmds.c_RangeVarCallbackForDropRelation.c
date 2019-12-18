#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct DropRelationCallbackState {char relkind; scalar_t__ heapOid; scalar_t__ partParentOid; scalar_t__ concurrent; } ;
struct TYPE_8__ {int relispartition; char relkind; int /*<<< orphan*/  relnamespace; } ;
struct TYPE_7__ {int indisvalid; } ;
struct TYPE_6__ {int /*<<< orphan*/  relname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_index ;
typedef  TYPE_3__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  DropErrorMsgWrongType (int /*<<< orphan*/ ,char,char) ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 scalar_t__ IndexGetRelation (scalar_t__,int) ; 
 void* InvalidOid ; 
 scalar_t__ IsSystemClass (scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  LockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 char RELKIND_INDEX ; 
 char RELKIND_PARTITIONED_INDEX ; 
 char RELKIND_PARTITIONED_TABLE ; 
 char RELKIND_RELATION ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  UnlockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowSystemTableMods ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_partition_parent (scalar_t__) ; 
 int /*<<< orphan*/  get_rel_relkind (scalar_t__) ; 
 int /*<<< orphan*/  get_relkind_objtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_class_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_namespace_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RangeVarCallbackForDropRelation(const RangeVar *rel, Oid relOid, Oid oldRelOid,
								void *arg)
{
	HeapTuple	tuple;
	struct DropRelationCallbackState *state;
	char		relkind;
	char		expected_relkind;
	bool		is_partition;
	Form_pg_class classform;
	LOCKMODE	heap_lockmode;
	bool		invalid_system_index = false;

	state = (struct DropRelationCallbackState *) arg;
	relkind = state->relkind;
	heap_lockmode = state->concurrent ?
		ShareUpdateExclusiveLock : AccessExclusiveLock;

	/*
	 * If we previously locked some other index's heap, and the name we're
	 * looking up no longer refers to that relation, release the now-useless
	 * lock.
	 */
	if (relOid != oldRelOid && OidIsValid(state->heapOid))
	{
		UnlockRelationOid(state->heapOid, heap_lockmode);
		state->heapOid = InvalidOid;
	}

	/*
	 * Similarly, if we previously locked some other partition's heap, and the
	 * name we're looking up no longer refers to that relation, release the
	 * now-useless lock.
	 */
	if (relOid != oldRelOid && OidIsValid(state->partParentOid))
	{
		UnlockRelationOid(state->partParentOid, AccessExclusiveLock);
		state->partParentOid = InvalidOid;
	}

	/* Didn't find a relation, so no need for locking or permission checks. */
	if (!OidIsValid(relOid))
		return;

	tuple = SearchSysCache1(RELOID, ObjectIdGetDatum(relOid));
	if (!HeapTupleIsValid(tuple))
		return;					/* concurrently dropped, so nothing to do */
	classform = (Form_pg_class) GETSTRUCT(tuple);
	is_partition = classform->relispartition;

	/*
	 * Both RELKIND_RELATION and RELKIND_PARTITIONED_TABLE are OBJECT_TABLE,
	 * but RemoveRelations() can only pass one relkind for a given relation.
	 * It chooses RELKIND_RELATION for both regular and partitioned tables.
	 * That means we must be careful before giving the wrong type error when
	 * the relation is RELKIND_PARTITIONED_TABLE.  An equivalent problem
	 * exists with indexes.
	 */
	if (classform->relkind == RELKIND_PARTITIONED_TABLE)
		expected_relkind = RELKIND_RELATION;
	else if (classform->relkind == RELKIND_PARTITIONED_INDEX)
		expected_relkind = RELKIND_INDEX;
	else
		expected_relkind = classform->relkind;

	if (relkind != expected_relkind)
		DropErrorMsgWrongType(rel->relname, classform->relkind, relkind);

	/* Allow DROP to either table owner or schema owner */
	if (!pg_class_ownercheck(relOid, GetUserId()) &&
		!pg_namespace_ownercheck(classform->relnamespace, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, get_relkind_objtype(get_rel_relkind(relOid)),
					   rel->relname);

	/*
	 * Check the case of a system index that might have been invalidated by a
	 * failed concurrent process and allow its drop. For the time being, this
	 * only concerns indexes of toast relations that became invalid during a
	 * REINDEX CONCURRENTLY process.
	 */
	if (IsSystemClass(relOid, classform) && relkind == RELKIND_INDEX)
	{
		HeapTuple	locTuple;
		Form_pg_index indexform;
		bool		indisvalid;

		locTuple = SearchSysCache1(INDEXRELID, ObjectIdGetDatum(relOid));
		if (!HeapTupleIsValid(locTuple))
		{
			ReleaseSysCache(tuple);
			return;
		}

		indexform = (Form_pg_index) GETSTRUCT(locTuple);
		indisvalid = indexform->indisvalid;
		ReleaseSysCache(locTuple);

		/* Mark object as being an invalid index of system catalogs */
		if (!indisvalid)
			invalid_system_index = true;
	}

	/* In the case of an invalid index, it is fine to bypass this check */
	if (!invalid_system_index && !allowSystemTableMods && IsSystemClass(relOid, classform))
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied: \"%s\" is a system catalog",
						rel->relname)));

	ReleaseSysCache(tuple);

	/*
	 * In DROP INDEX, attempt to acquire lock on the parent table before
	 * locking the index.  index_drop() will need this anyway, and since
	 * regular queries lock tables before their indexes, we risk deadlock if
	 * we do it the other way around.  No error if we don't find a pg_index
	 * entry, though --- the relation may have been dropped.
	 */
	if ((relkind == RELKIND_INDEX || relkind == RELKIND_PARTITIONED_INDEX) &&
		relOid != oldRelOid)
	{
		state->heapOid = IndexGetRelation(relOid, true);
		if (OidIsValid(state->heapOid))
			LockRelationOid(state->heapOid, heap_lockmode);
	}

	/*
	 * Similarly, if the relation is a partition, we must acquire lock on its
	 * parent before locking the partition.  That's because queries lock the
	 * parent before its partitions, so we risk deadlock it we do it the other
	 * way around.
	 */
	if (is_partition && relOid != oldRelOid)
	{
		state->partParentOid = get_partition_parent(relOid);
		if (OidIsValid(state->partParentOid))
			LockRelationOid(state->partParentOid, AccessExclusiveLock);
	}
}