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

/* Variables and functions */
 int /*<<< orphan*/  CheckSlotRequirements () ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ MyDatabaseId ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ WAL_LEVEL_LOGICAL ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ wal_level ; 

void
CheckLogicalDecodingRequirements(void)
{
	CheckSlotRequirements();

	/*
	 * NB: Adding a new requirement likely means that RestoreSlotFromDisk()
	 * needs the same check.
	 */

	if (wal_level < WAL_LEVEL_LOGICAL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("logical decoding requires wal_level >= logical")));

	if (MyDatabaseId == InvalidOid)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("logical decoding requires a database connection")));

	/* ----
	 * TODO: We got to change that someday soon...
	 *
	 * There's basically three things missing to allow this:
	 * 1) We need to be able to correctly and quickly identify the timeline a
	 *	  LSN belongs to
	 * 2) We need to force hot_standby_feedback to be enabled at all times so
	 *	  the primary cannot remove rows we need.
	 * 3) support dropping replication slots referring to a database, in
	 *	  dbase_redo. There can't be any active ones due to HS recovery
	 *	  conflicts, so that should be relatively easy.
	 * ----
	 */
	if (RecoveryInProgress())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("logical decoding cannot be used while in recovery")));
}