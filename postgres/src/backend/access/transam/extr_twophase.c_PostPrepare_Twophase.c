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
struct TYPE_2__ {int /*<<< orphan*/  locking_backend; } ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidBackendId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* MyLockedGxact ; 
 int /*<<< orphan*/  TwoPhaseStateLock ; 

void
PostPrepare_Twophase(void)
{
	LWLockAcquire(TwoPhaseStateLock, LW_EXCLUSIVE);
	MyLockedGxact->locking_backend = InvalidBackendId;
	LWLockRelease(TwoPhaseStateLock);

	MyLockedGxact = NULL;
}