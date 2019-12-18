#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_4__ {scalar_t__ currTLI; int /*<<< orphan*/  nextTLI; int /*<<< orphan*/  currTLIValidUntil; } ;
typedef  TYPE_1__ XLogReaderState ;

/* Variables and functions */
 scalar_t__ ThisTimeLineID ; 
 scalar_t__ WalSndWaitForWal (scalar_t__) ; 
 int XLOG_BLCKSZ ; 
 int /*<<< orphan*/  XLogRead (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  XLogReadDetermineTimeline (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  sendCxt ; 
 scalar_t__ sendTimeLine ; 
 int sendTimeLineIsHistoric ; 
 int /*<<< orphan*/  sendTimeLineNextTLI ; 
 int /*<<< orphan*/  sendTimeLineValidUpto ; 

__attribute__((used)) static int
logical_read_xlog_page(XLogReaderState *state, XLogRecPtr targetPagePtr, int reqLen,
					   XLogRecPtr targetRecPtr, char *cur_page)
{
	XLogRecPtr	flushptr;
	int			count;

	XLogReadDetermineTimeline(state, targetPagePtr, reqLen);
	sendTimeLineIsHistoric = (state->currTLI != ThisTimeLineID);
	sendTimeLine = state->currTLI;
	sendTimeLineValidUpto = state->currTLIValidUntil;
	sendTimeLineNextTLI = state->nextTLI;

	/* make sure we have enough WAL available */
	flushptr = WalSndWaitForWal(targetPagePtr + reqLen);

	/* fail if not (implies we are going to shut down) */
	if (flushptr < targetPagePtr + reqLen)
		return -1;

	if (targetPagePtr + XLOG_BLCKSZ <= flushptr)
		count = XLOG_BLCKSZ;	/* more than one block available */
	else
		count = flushptr - targetPagePtr;	/* part of the page available */

	/* now actually read the data, we know it's there */
	XLogRead(sendCxt, cur_page, targetPagePtr, XLOG_BLCKSZ);

	return count;
}