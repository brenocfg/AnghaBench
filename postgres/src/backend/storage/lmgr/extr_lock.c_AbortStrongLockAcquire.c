#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_5__ {scalar_t__* count; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {int holdsStrongLockCount; int /*<<< orphan*/  hashcode; } ;
typedef  TYPE_1__ LOCALLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t FastPathStrongLockHashPartition (int /*<<< orphan*/ ) ; 
 TYPE_3__* FastPathStrongRelationLocks ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* StrongLockInProgress ; 

void
AbortStrongLockAcquire(void)
{
	uint32		fasthashcode;
	LOCALLOCK  *locallock = StrongLockInProgress;

	if (locallock == NULL)
		return;

	fasthashcode = FastPathStrongLockHashPartition(locallock->hashcode);
	Assert(locallock->holdsStrongLockCount == true);
	SpinLockAcquire(&FastPathStrongRelationLocks->mutex);
	Assert(FastPathStrongRelationLocks->count[fasthashcode] > 0);
	FastPathStrongRelationLocks->count[fasthashcode]--;
	locallock->holdsStrongLockCount = false;
	StrongLockInProgress = NULL;
	SpinLockRelease(&FastPathStrongRelationLocks->mutex);
}