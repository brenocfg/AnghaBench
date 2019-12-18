#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_6__ {int nRequested; } ;
struct TYPE_5__ {scalar_t__ locktag_lockmethodid; } ;
typedef  int /*<<< orphan*/  LWLock ;
typedef  TYPE_1__ LOCKTAG ;
typedef  scalar_t__ LOCKMETHODID ;
typedef  TYPE_2__ LOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/ * LockHashPartitionLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockMethodLockHash ; 
 int /*<<< orphan*/  LockMethods ; 
 int /*<<< orphan*/  LockTagHashCode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ lengthof (int /*<<< orphan*/ ) ; 

int
LockWaiterCount(const LOCKTAG *locktag)
{
	LOCKMETHODID lockmethodid = locktag->locktag_lockmethodid;
	LOCK	   *lock;
	bool		found;
	uint32		hashcode;
	LWLock	   *partitionLock;
	int			waiters = 0;

	if (lockmethodid <= 0 || lockmethodid >= lengthof(LockMethods))
		elog(ERROR, "unrecognized lock method: %d", lockmethodid);

	hashcode = LockTagHashCode(locktag);
	partitionLock = LockHashPartitionLock(hashcode);
	LWLockAcquire(partitionLock, LW_EXCLUSIVE);

	lock = (LOCK *) hash_search_with_hash_value(LockMethodLockHash,
												(const void *) locktag,
												hashcode,
												HASH_FIND,
												&found);
	if (found)
	{
		Assert(lock != NULL);
		waiters = lock->nRequested;
	}
	LWLockRelease(partitionLock);

	return waiters;
}