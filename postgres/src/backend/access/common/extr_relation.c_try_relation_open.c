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
typedef  int /*<<< orphan*/ * Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CheckRelationLockedByMe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MAX_LOCKMODES ; 
 int /*<<< orphan*/  MyXactFlags ; 
 scalar_t__ NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/ * RelationIdGetRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIsValid (int /*<<< orphan*/ *) ; 
 scalar_t__ RelationUsesLocalBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SearchSysCacheExists1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationOid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XACT_FLAGS_ACCESSEDTEMPNAMESPACE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_initstats (int /*<<< orphan*/ *) ; 

Relation
try_relation_open(Oid relationId, LOCKMODE lockmode)
{
	Relation	r;

	Assert(lockmode >= NoLock && lockmode < MAX_LOCKMODES);

	/* Get the lock first */
	if (lockmode != NoLock)
		LockRelationOid(relationId, lockmode);

	/*
	 * Now that we have the lock, probe to see if the relation really exists
	 * or not.
	 */
	if (!SearchSysCacheExists1(RELOID, ObjectIdGetDatum(relationId)))
	{
		/* Release useless lock */
		if (lockmode != NoLock)
			UnlockRelationOid(relationId, lockmode);

		return NULL;
	}

	/* Should be safe to do a relcache load */
	r = RelationIdGetRelation(relationId);

	if (!RelationIsValid(r))
		elog(ERROR, "could not open relation with OID %u", relationId);

	/* If we didn't get the lock ourselves, assert that caller holds one */
	Assert(lockmode != NoLock ||
		   CheckRelationLockedByMe(r, AccessShareLock, true));

	/* Make note that we've accessed a temporary relation */
	if (RelationUsesLocalBuffers(r))
		MyXactFlags |= XACT_FLAGS_ACCESSEDTEMPNAMESPACE;

	pgstat_initstats(r);

	return r;
}