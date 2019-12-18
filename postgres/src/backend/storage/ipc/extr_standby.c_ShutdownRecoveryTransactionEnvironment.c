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
 int /*<<< orphan*/  ExpireAllKnownAssignedTransactionIds () ; 
 int /*<<< orphan*/ * RecoveryLockLists ; 
 int /*<<< orphan*/  StandbyReleaseAllLocks () ; 
 int /*<<< orphan*/  VirtualXactLockTableCleanup () ; 
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 

void
ShutdownRecoveryTransactionEnvironment(void)
{
	/* Mark all tracked in-progress transactions as finished. */
	ExpireAllKnownAssignedTransactionIds();

	/* Release all locks the tracked transactions were holding */
	StandbyReleaseAllLocks();

	/* Destroy the hash table of locks. */
	hash_destroy(RecoveryLockLists);
	RecoveryLockLists = NULL;

	/* Cleanup our VirtualTransaction */
	VirtualXactLockTableCleanup();
}