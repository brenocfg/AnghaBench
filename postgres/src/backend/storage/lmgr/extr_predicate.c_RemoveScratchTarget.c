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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PredicateLockTargetHash ; 
 int /*<<< orphan*/  ScratchPartitionLock ; 
 int /*<<< orphan*/  ScratchTargetTag ; 
 int /*<<< orphan*/  ScratchTargetTagHash ; 
 int /*<<< orphan*/  SerializablePredicateLockListLock ; 
 int /*<<< orphan*/  hash_search_with_hash_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
RemoveScratchTarget(bool lockheld)
{
	bool		found;

	Assert(LWLockHeldByMe(SerializablePredicateLockListLock));

	if (!lockheld)
		LWLockAcquire(ScratchPartitionLock, LW_EXCLUSIVE);
	hash_search_with_hash_value(PredicateLockTargetHash,
								&ScratchTargetTag,
								ScratchTargetTagHash,
								HASH_REMOVE, &found);
	Assert(found);
	if (!lockheld)
		LWLockRelease(ScratchPartitionLock);
}