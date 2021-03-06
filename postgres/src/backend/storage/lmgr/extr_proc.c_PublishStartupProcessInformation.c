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
struct TYPE_2__ {int /*<<< orphan*/  startupProcPid; int /*<<< orphan*/  startupProc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MyProc ; 
 int /*<<< orphan*/  MyProcPid ; 
 TYPE_1__* ProcGlobal ; 
 int /*<<< orphan*/  ProcStructLock ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ ) ; 

void
PublishStartupProcessInformation(void)
{
	SpinLockAcquire(ProcStructLock);

	ProcGlobal->startupProc = MyProc;
	ProcGlobal->startupProcPid = MyProcPid;

	SpinLockRelease(ProcStructLock);
}