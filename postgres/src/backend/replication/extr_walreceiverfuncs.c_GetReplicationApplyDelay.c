#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_3__ {scalar_t__ receivedUpto; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ WalRcvData ;
typedef  scalar_t__ TimestampTz ;

/* Variables and functions */
 scalar_t__ GetCurrentChunkReplayStartTime () ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 scalar_t__ GetXLogReplayRecPtr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TimestampDifference (scalar_t__,int /*<<< orphan*/ ,long*,int*) ; 
 TYPE_1__* WalRcv ; 

int
GetReplicationApplyDelay(void)
{
	WalRcvData *walrcv = WalRcv;
	XLogRecPtr	receivePtr;
	XLogRecPtr	replayPtr;

	long		secs;
	int			usecs;

	TimestampTz chunkReplayStartTime;

	SpinLockAcquire(&walrcv->mutex);
	receivePtr = walrcv->receivedUpto;
	SpinLockRelease(&walrcv->mutex);

	replayPtr = GetXLogReplayRecPtr(NULL);

	if (receivePtr == replayPtr)
		return 0;

	chunkReplayStartTime = GetCurrentChunkReplayStartTime();

	if (chunkReplayStartTime == 0)
		return -1;

	TimestampDifference(chunkReplayStartTime,
						GetCurrentTimestamp(),
						&secs, &usecs);

	return (((int) secs * 1000) + (usecs / 1000));
}