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
typedef  int /*<<< orphan*/  XLogRecPtr ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  receivedTLI; int /*<<< orphan*/  latestChunkStart; int /*<<< orphan*/  receivedUpto; } ;
typedef  TYPE_1__ WalRcvData ;
typedef  int /*<<< orphan*/  TimeLineID ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* WalRcv ; 

XLogRecPtr
GetWalRcvWriteRecPtr(XLogRecPtr *latestChunkStart, TimeLineID *receiveTLI)
{
	WalRcvData *walrcv = WalRcv;
	XLogRecPtr	recptr;

	SpinLockAcquire(&walrcv->mutex);
	recptr = walrcv->receivedUpto;
	if (latestChunkStart)
		*latestChunkStart = walrcv->latestChunkStart;
	if (receiveTLI)
		*receiveTLI = walrcv->receivedTLI;
	SpinLockRelease(&walrcv->mutex);

	return recptr;
}