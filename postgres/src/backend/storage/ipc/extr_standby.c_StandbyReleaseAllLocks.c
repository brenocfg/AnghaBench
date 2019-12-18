#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  locks; } ;
typedef  TYPE_1__ RecoveryLockListsEntry ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 int /*<<< orphan*/  RecoveryLockLists ; 
 int /*<<< orphan*/  StandbyReleaseLockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_recovery (int /*<<< orphan*/ ) ; 

void
StandbyReleaseAllLocks(void)
{
	HASH_SEQ_STATUS status;
	RecoveryLockListsEntry *entry;

	elog(trace_recovery(DEBUG2), "release all standby locks");

	hash_seq_init(&status, RecoveryLockLists);
	while ((entry = hash_seq_search(&status)))
	{
		StandbyReleaseLockList(entry->locks);
		hash_search(RecoveryLockLists, entry, HASH_REMOVE, NULL);
	}
}