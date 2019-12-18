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
typedef  int /*<<< orphan*/  Oid ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CheckRelationLockedByMe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ MAX_LOCKMODES ; 
 int /*<<< orphan*/  MyXactFlags ; 
 scalar_t__ NoLock ; 
 int /*<<< orphan*/  RelationIdGetRelation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationUsesLocalBuffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XACT_FLAGS_ACCESSEDTEMPNAMESPACE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_initstats (int /*<<< orphan*/ ) ; 

Relation
relation_open(Oid relationId, LOCKMODE lockmode)
{
	Relation	r;

	Assert(lockmode >= NoLock && lockmode < MAX_LOCKMODES);

	/* Get the lock before trying to open the relcache entry */
	if (lockmode != NoLock)
		LockRelationOid(relationId, lockmode);

	/* The relcache does all the real work... */
	r = RelationIdGetRelation(relationId);

	if (!RelationIsValid(r))
		elog(ERROR, "could not open relation with OID %u", relationId);

	/*
	 * If we didn't get the lock ourselves, assert that caller holds one,
	 * except in bootstrap mode where no locks are used.
	 */
	Assert(lockmode != NoLock ||
		   IsBootstrapProcessingMode() ||
		   CheckRelationLockedByMe(r, AccessShareLock, true));

	/* Make note that we've accessed a temporary relation */
	if (RelationUsesLocalBuffers(r))
		MyXactFlags |= XACT_FLAGS_ACCESSEDTEMPNAMESPACE;

	pgstat_initstats(r);

	return r;
}