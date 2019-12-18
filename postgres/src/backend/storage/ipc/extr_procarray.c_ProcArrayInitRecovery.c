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
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ STANDBY_INITIALIZED ; 
 int TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdRetreat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latestObservedXid ; 
 scalar_t__ standbyState ; 

void
ProcArrayInitRecovery(TransactionId initializedUptoXID)
{
	Assert(standbyState == STANDBY_INITIALIZED);
	Assert(TransactionIdIsNormal(initializedUptoXID));

	/*
	 * we set latestObservedXid to the xid SUBTRANS has been initialized up
	 * to, so we can extend it from that point onwards in
	 * RecordKnownAssignedTransactionIds, and when we get consistent in
	 * ProcArrayApplyRecoveryInfo().
	 */
	latestObservedXid = initializedUptoXID;
	TransactionIdRetreat(latestObservedXid);
}