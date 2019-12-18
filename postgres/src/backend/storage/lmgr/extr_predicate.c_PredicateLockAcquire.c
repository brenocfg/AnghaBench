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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_2__ {int held; scalar_t__ childLocks; } ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  TYPE_1__ LOCALPREDICATELOCK ;

/* Variables and functions */
 scalar_t__ CheckAndPromotePredicateLockRequest (int /*<<< orphan*/  const*) ; 
 scalar_t__ CoarserLockCovers (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CreatePredicateLock (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteChildTargetLocks (int /*<<< orphan*/  const*) ; 
 scalar_t__ GET_PREDICATELOCKTARGETTAG_TYPE (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  LocalPredicateLockHash ; 
 int /*<<< orphan*/  MySerializableXact ; 
 scalar_t__ PREDLOCKTAG_TUPLE ; 
 scalar_t__ PredicateLockExists (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PredicateLockTargetTagHashCode (int /*<<< orphan*/  const*) ; 
 scalar_t__ hash_search_with_hash_value (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
PredicateLockAcquire(const PREDICATELOCKTARGETTAG *targettag)
{
	uint32		targettaghash;
	bool		found;
	LOCALPREDICATELOCK *locallock;

	/* Do we have the lock already, or a covering lock? */
	if (PredicateLockExists(targettag))
		return;

	if (CoarserLockCovers(targettag))
		return;

	/* the same hash and LW lock apply to the lock target and the local lock. */
	targettaghash = PredicateLockTargetTagHashCode(targettag);

	/* Acquire lock in local table */
	locallock = (LOCALPREDICATELOCK *)
		hash_search_with_hash_value(LocalPredicateLockHash,
									targettag, targettaghash,
									HASH_ENTER, &found);
	locallock->held = true;
	if (!found)
		locallock->childLocks = 0;

	/* Actually create the lock */
	CreatePredicateLock(targettag, targettaghash, MySerializableXact);

	/*
	 * Lock has been acquired. Check whether it should be promoted to a
	 * coarser granularity, or whether there are finer-granularity locks to
	 * clean up.
	 */
	if (CheckAndPromotePredicateLockRequest(targettag))
	{
		/*
		 * Lock request was promoted to a coarser-granularity lock, and that
		 * lock was acquired. It will delete this lock and any of its
		 * children, so we're done.
		 */
	}
	else
	{
		/* Clean up any finer-granularity locks */
		if (GET_PREDICATELOCKTARGETTAG_TYPE(*targettag) != PREDLOCKTAG_TUPLE)
			DeleteChildTargetLocks(targettag);
	}
}