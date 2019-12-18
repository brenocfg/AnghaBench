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
#define  SYNCHRONOUS_COMMIT_REMOTE_APPLY 130 
#define  SYNCHRONOUS_COMMIT_REMOTE_FLUSH 129 
#define  SYNCHRONOUS_COMMIT_REMOTE_WRITE 128 
 int /*<<< orphan*/  SYNC_REP_NO_WAIT ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_APPLY ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_FLUSH ; 
 int /*<<< orphan*/  SYNC_REP_WAIT_WRITE ; 
 int /*<<< orphan*/  SyncRepWaitMode ; 

void
assign_synchronous_commit(int newval, void *extra)
{
	switch (newval)
	{
		case SYNCHRONOUS_COMMIT_REMOTE_WRITE:
			SyncRepWaitMode = SYNC_REP_WAIT_WRITE;
			break;
		case SYNCHRONOUS_COMMIT_REMOTE_FLUSH:
			SyncRepWaitMode = SYNC_REP_WAIT_FLUSH;
			break;
		case SYNCHRONOUS_COMMIT_REMOTE_APPLY:
			SyncRepWaitMode = SYNC_REP_WAIT_APPLY;
			break;
		default:
			SyncRepWaitMode = SYNC_REP_NO_WAIT;
			break;
	}
}