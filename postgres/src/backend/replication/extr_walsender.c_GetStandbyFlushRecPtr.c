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
typedef  scalar_t__ XLogRecPtr ;
typedef  scalar_t__ TimeLineID ;

/* Variables and functions */
 scalar_t__ GetWalRcvWriteRecPtr (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ GetXLogReplayRecPtr (scalar_t__*) ; 
 scalar_t__ ThisTimeLineID ; 

__attribute__((used)) static XLogRecPtr
GetStandbyFlushRecPtr(void)
{
	XLogRecPtr	replayPtr;
	TimeLineID	replayTLI;
	XLogRecPtr	receivePtr;
	TimeLineID	receiveTLI;
	XLogRecPtr	result;

	/*
	 * We can safely send what's already been replayed. Also, if walreceiver
	 * is streaming WAL from the same timeline, we can send anything that it
	 * has streamed, but hasn't been replayed yet.
	 */

	receivePtr = GetWalRcvWriteRecPtr(NULL, &receiveTLI);
	replayPtr = GetXLogReplayRecPtr(&replayTLI);

	ThisTimeLineID = replayTLI;

	result = replayPtr;
	if (receiveTLI == ThisTimeLineID && receivePtr > replayPtr)
		result = receivePtr;

	return result;
}