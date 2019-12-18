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
typedef  scalar_t__ LOCKMETHODID ;
typedef  int /*<<< orphan*/  LOCALLOCK ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ LOCALLOCK_LOCKMETHOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockMethodLocalHash ; 
 int /*<<< orphan*/  LockMethods ; 
 int /*<<< orphan*/  ReleaseLockIfHeld (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hash_seq_search (int /*<<< orphan*/ *) ; 
 scalar_t__ lengthof (int /*<<< orphan*/ ) ; 

void
LockReleaseSession(LOCKMETHODID lockmethodid)
{
	HASH_SEQ_STATUS status;
	LOCALLOCK  *locallock;

	if (lockmethodid <= 0 || lockmethodid >= lengthof(LockMethods))
		elog(ERROR, "unrecognized lock method: %d", lockmethodid);

	hash_seq_init(&status, LockMethodLocalHash);

	while ((locallock = (LOCALLOCK *) hash_seq_search(&status)) != NULL)
	{
		/* Ignore items that are not of the specified lock method */
		if (LOCALLOCK_LOCKMETHOD(*locallock) != lockmethodid)
			continue;

		ReleaseLockIfHeld(locallock, true);
	}
}