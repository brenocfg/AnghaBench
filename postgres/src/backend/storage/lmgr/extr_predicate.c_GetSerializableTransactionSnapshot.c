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
typedef  int /*<<< orphan*/  Snapshot ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetSafeSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetSerializableTransactionSnapshotInt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidPid ; 
 int /*<<< orphan*/  IsolationIsSerializable () ; 
 scalar_t__ RecoveryInProgress () ; 
 scalar_t__ XactDeferrable ; 
 scalar_t__ XactReadOnly ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

Snapshot
GetSerializableTransactionSnapshot(Snapshot snapshot)
{
	Assert(IsolationIsSerializable());

	/*
	 * Can't use serializable mode while recovery is still active, as it is,
	 * for example, on a hot standby.  We could get here despite the check in
	 * check_XactIsoLevel() if default_transaction_isolation is set to
	 * serializable, so phrase the hint accordingly.
	 */
	if (RecoveryInProgress())
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot use serializable mode in a hot standby"),
				 errdetail("\"default_transaction_isolation\" is set to \"serializable\"."),
				 errhint("You can use \"SET default_transaction_isolation = 'repeatable read'\" to change the default.")));

	/*
	 * A special optimization is available for SERIALIZABLE READ ONLY
	 * DEFERRABLE transactions -- we can wait for a suitable snapshot and
	 * thereby avoid all SSI overhead once it's running.
	 */
	if (XactReadOnly && XactDeferrable)
		return GetSafeSnapshot(snapshot);

	return GetSerializableTransactionSnapshotInt(snapshot,
												 NULL, InvalidPid);
}