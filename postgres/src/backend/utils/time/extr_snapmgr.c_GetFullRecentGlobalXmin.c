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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ TransactionId ;
typedef  int /*<<< orphan*/  FullTransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FullTransactionIdFromEpochAndXid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ReadNextFullTransactionId () ; 
 scalar_t__ RecentGlobalXmin ; 
 int /*<<< orphan*/  TransactionIdIsNormal (scalar_t__) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 

FullTransactionId
GetFullRecentGlobalXmin(void)
{
	FullTransactionId nextxid_full;
	uint32		nextxid_epoch;
	TransactionId nextxid_xid;
	uint32		epoch;

	Assert(TransactionIdIsNormal(RecentGlobalXmin));

	/*
	 * Compute the epoch from the next XID's epoch. This relies on the fact
	 * that RecentGlobalXmin must be within the 2 billion XID horizon from the
	 * next XID.
	 */
	nextxid_full = ReadNextFullTransactionId();
	nextxid_epoch = EpochFromFullTransactionId(nextxid_full);
	nextxid_xid = XidFromFullTransactionId(nextxid_full);

	if (RecentGlobalXmin > nextxid_xid)
		epoch = nextxid_epoch - 1;
	else
		epoch = nextxid_epoch;

	return FullTransactionIdFromEpochAndXid(epoch, RecentGlobalXmin);
}