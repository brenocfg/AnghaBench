#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  TimeLineID ;
struct TYPE_2__ {int /*<<< orphan*/  info_lck; int /*<<< orphan*/  lastReplayedTLI; int /*<<< orphan*/  lastReplayedEndRecPtr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* XLogCtl ; 

XLogRecPtr
GetXLogReplayRecPtr(TimeLineID *replayTLI)
{
	XLogRecPtr	recptr;
	TimeLineID	tli;

	SpinLockAcquire(&XLogCtl->info_lck);
	recptr = XLogCtl->lastReplayedEndRecPtr;
	tli = XLogCtl->lastReplayedTLI;
	SpinLockRelease(&XLogCtl->info_lck);

	if (replayTLI)
		*replayTLI = tli;
	return recptr;
}