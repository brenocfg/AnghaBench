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
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_2__ {scalar_t__ roident; scalar_t__ local_lsn; scalar_t__ remote_lsn; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ InvalidRepOriginId ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* session_replication_state ; 

void
replorigin_session_advance(XLogRecPtr remote_commit, XLogRecPtr local_commit)
{
	Assert(session_replication_state != NULL);
	Assert(session_replication_state->roident != InvalidRepOriginId);

	LWLockAcquire(&session_replication_state->lock, LW_EXCLUSIVE);
	if (session_replication_state->local_lsn < local_commit)
		session_replication_state->local_lsn = local_commit;
	if (session_replication_state->remote_lsn < remote_commit)
		session_replication_state->remote_lsn = remote_commit;
	LWLockRelease(&session_replication_state->lock);
}