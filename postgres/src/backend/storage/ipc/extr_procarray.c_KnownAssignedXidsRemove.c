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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  KnownAssignedXidsSearch (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
KnownAssignedXidsRemove(TransactionId xid)
{
	Assert(TransactionIdIsValid(xid));

	elog(trace_recovery(DEBUG4), "remove KnownAssignedXid %u", xid);

	/*
	 * Note: we cannot consider it an error to remove an XID that's not
	 * present.  We intentionally remove subxact IDs while processing
	 * XLOG_XACT_ASSIGNMENT, to avoid array overflow.  Then those XIDs will be
	 * removed again when the top-level xact commits or aborts.
	 *
	 * It might be possible to track such XIDs to distinguish this case from
	 * actual errors, but it would be complicated and probably not worth it.
	 * So, just ignore the search result.
	 */
	(void) KnownAssignedXidsSearch(xid, true);
}