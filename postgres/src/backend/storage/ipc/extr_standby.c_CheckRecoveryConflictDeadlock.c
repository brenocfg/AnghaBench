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
 int /*<<< orphan*/  ERRCODE_T_R_DEADLOCK_DETECTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HoldingBufferPinThatDelaysRecovery () ; 
 int /*<<< orphan*/  InRecovery ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

void
CheckRecoveryConflictDeadlock(void)
{
	Assert(!InRecovery);		/* do not call in Startup process */

	if (!HoldingBufferPinThatDelaysRecovery())
		return;

	/*
	 * Error message should match ProcessInterrupts() but we avoid calling
	 * that because we aren't handling an interrupt at this point. Note that
	 * we only cancel the current transaction here, so if we are in a
	 * subtransaction and the pin is held by a parent, then the Startup
	 * process will continue to wait even though we have avoided deadlock.
	 */
	ereport(ERROR,
			(errcode(ERRCODE_T_R_DEADLOCK_DETECTED),
			 errmsg("canceling statement due to conflict with recovery"),
			 errdetail("User transaction caused buffer deadlock with recovery.")));
}