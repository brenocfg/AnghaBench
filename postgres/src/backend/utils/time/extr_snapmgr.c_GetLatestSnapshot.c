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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FirstSnapshotSet ; 
 int /*<<< orphan*/  GetSnapshotData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  HistoricSnapshotActive () ; 
 scalar_t__ IsInParallelMode () ; 
 int /*<<< orphan*/  SecondarySnapshot ; 
 int /*<<< orphan*/  SecondarySnapshotData ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

Snapshot
GetLatestSnapshot(void)
{
	/*
	 * We might be able to relax this, but nothing that could otherwise work
	 * needs it.
	 */
	if (IsInParallelMode())
		elog(ERROR,
			 "cannot update SecondarySnapshot during a parallel operation");

	/*
	 * So far there are no cases requiring support for GetLatestSnapshot()
	 * during logical decoding, but it wouldn't be hard to add if required.
	 */
	Assert(!HistoricSnapshotActive());

	/* If first call in transaction, go ahead and set the xact snapshot */
	if (!FirstSnapshotSet)
		return GetTransactionSnapshot();

	SecondarySnapshot = GetSnapshotData(&SecondarySnapshotData);

	return SecondarySnapshot;
}