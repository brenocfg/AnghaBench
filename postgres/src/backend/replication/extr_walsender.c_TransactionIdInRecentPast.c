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
 scalar_t__ EpochFromFullTransactionId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadNextFullTransactionId () ; 
 int /*<<< orphan*/  TransactionIdPrecedesOrEquals (scalar_t__,scalar_t__) ; 
 scalar_t__ XidFromFullTransactionId (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
TransactionIdInRecentPast(TransactionId xid, uint32 epoch)
{
	FullTransactionId nextFullXid;
	TransactionId nextXid;
	uint32		nextEpoch;

	nextFullXid = ReadNextFullTransactionId();
	nextXid = XidFromFullTransactionId(nextFullXid);
	nextEpoch = EpochFromFullTransactionId(nextFullXid);

	if (xid <= nextXid)
	{
		if (epoch != nextEpoch)
			return false;
	}
	else
	{
		if (epoch + 1 != nextEpoch)
			return false;
	}

	if (!TransactionIdPrecedesOrEquals(xid, nextXid))
		return false;			/* epoch OK, but it's wrapped around */

	return true;
}