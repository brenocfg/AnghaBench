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
typedef  scalar_t__ ProcSignalReason ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CancelDBBackends (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ PROCSIG_RECOVERY_CONFLICT_BUFFERPIN ; 
 scalar_t__ PROCSIG_RECOVERY_CONFLICT_STARTUP_DEADLOCK ; 

__attribute__((used)) static void
SendRecoveryConflictWithBufferPin(ProcSignalReason reason)
{
	Assert(reason == PROCSIG_RECOVERY_CONFLICT_BUFFERPIN ||
		   reason == PROCSIG_RECOVERY_CONFLICT_STARTUP_DEADLOCK);

	/*
	 * We send signal to all backends to ask them if they are holding the
	 * buffer pin which is delaying the Startup process. We must not set the
	 * conflict flag yet, since most backends will be innocent. Let the
	 * SIGUSR1 handling in each backend decide their own fate.
	 */
	CancelDBBackends(InvalidOid, reason, false);
}