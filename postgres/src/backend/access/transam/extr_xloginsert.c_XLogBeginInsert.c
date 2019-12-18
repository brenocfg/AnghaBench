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
typedef  int /*<<< orphan*/  XLogRecData ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  XLogInsertAllowed () ; 
 int begininsert_called ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mainrdata_head ; 
 int /*<<< orphan*/ * mainrdata_last ; 
 scalar_t__ mainrdata_len ; 
 scalar_t__ max_registered_block_id ; 

void
XLogBeginInsert(void)
{
	Assert(max_registered_block_id == 0);
	Assert(mainrdata_last == (XLogRecData *) &mainrdata_head);
	Assert(mainrdata_len == 0);

	/* cross-check on whether we should be here or not */
	if (!XLogInsertAllowed())
		elog(ERROR, "cannot make new WAL entries during recovery");

	if (begininsert_called)
		elog(ERROR, "XLogBeginInsert was already called");

	begininsert_called = true;
}