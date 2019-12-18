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
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_2__ {int /*<<< orphan*/  info_lck; int /*<<< orphan*/  recoveryLastXTime; } ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* XLogCtl ; 

TimestampTz
GetLatestXTime(void)
{
	TimestampTz xtime;

	SpinLockAcquire(&XLogCtl->info_lck);
	xtime = XLogCtl->recoveryLastXTime;
	SpinLockRelease(&XLogCtl->info_lck);

	return xtime;
}