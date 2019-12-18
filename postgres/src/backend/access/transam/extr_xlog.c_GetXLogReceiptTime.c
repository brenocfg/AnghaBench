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
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InRecovery ; 
 scalar_t__ XLOG_FROM_STREAM ; 
 scalar_t__ XLogReceiptSource ; 
 int /*<<< orphan*/  XLogReceiptTime ; 

void
GetXLogReceiptTime(TimestampTz *rtime, bool *fromStream)
{
	/*
	 * This must be executed in the startup process, since we don't export the
	 * relevant state to shared memory.
	 */
	Assert(InRecovery);

	*rtime = XLogReceiptTime;
	*fromStream = (XLogReceiptSource == XLOG_FROM_STREAM);
}