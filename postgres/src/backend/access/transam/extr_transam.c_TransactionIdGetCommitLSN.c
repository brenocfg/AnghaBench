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
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TransactionId ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidXLogRecPtr ; 
 scalar_t__ TransactionIdEquals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TransactionIdGetStatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cachedCommitLSN ; 
 int /*<<< orphan*/  cachedFetchXid ; 

XLogRecPtr
TransactionIdGetCommitLSN(TransactionId xid)
{
	XLogRecPtr	result;

	/*
	 * Currently, all uses of this function are for xids that were just
	 * reported to be committed by TransactionLogFetch, so we expect that
	 * checking TransactionLogFetch's cache will usually succeed and avoid an
	 * extra trip to shared memory.
	 */
	if (TransactionIdEquals(xid, cachedFetchXid))
		return cachedCommitLSN;

	/* Special XIDs are always known committed */
	if (!TransactionIdIsNormal(xid))
		return InvalidXLogRecPtr;

	/*
	 * Get the transaction status.
	 */
	(void) TransactionIdGetStatus(xid, &result);

	return result;
}