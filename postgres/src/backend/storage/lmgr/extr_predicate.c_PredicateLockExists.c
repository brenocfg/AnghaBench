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
struct TYPE_2__ {int held; } ;
typedef  int /*<<< orphan*/  PREDICATELOCKTARGETTAG ;
typedef  TYPE_1__ LOCALPREDICATELOCK ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  LocalPredicateLockHash ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
PredicateLockExists(const PREDICATELOCKTARGETTAG *targettag)
{
	LOCALPREDICATELOCK *lock;

	/* check local hash table */
	lock = (LOCALPREDICATELOCK *) hash_search(LocalPredicateLockHash,
											  targettag,
											  HASH_FIND, NULL);

	if (!lock)
		return false;

	/*
	 * Found entry in the table, but still need to check whether it's actually
	 * held -- it could just be a parent of some held lock.
	 */
	return lock->held;
}