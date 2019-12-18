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
 int /*<<< orphan*/  Async_UnlistenAll () ; 
 int /*<<< orphan*/  DropAllPreparedStatements () ; 
 int /*<<< orphan*/  LockReleaseAll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  PortalHashTableDeleteAll () ; 
 int /*<<< orphan*/  PreventInTransactionBlock (int,char*) ; 
 int /*<<< orphan*/  ResetAllOptions () ; 
 int /*<<< orphan*/  ResetPlanCache () ; 
 int /*<<< orphan*/  ResetSequenceCaches () ; 
 int /*<<< orphan*/  ResetTempTableNamespace () ; 
 int /*<<< orphan*/  SetPGVariable (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USER_LOCKMETHOD ; 

__attribute__((used)) static void
DiscardAll(bool isTopLevel)
{
	/*
	 * Disallow DISCARD ALL in a transaction block. This is arguably
	 * inconsistent (we don't make a similar check in the command sequence
	 * that DISCARD ALL is equivalent to), but the idea is to catch mistakes:
	 * DISCARD ALL inside a transaction block would leave the transaction
	 * still uncommitted.
	 */
	PreventInTransactionBlock(isTopLevel, "DISCARD ALL");

	/* Closing portals might run user-defined code, so do that first. */
	PortalHashTableDeleteAll();
	SetPGVariable("session_authorization", NIL, false);
	ResetAllOptions();
	DropAllPreparedStatements();
	Async_UnlistenAll();
	LockReleaseAll(USER_LOCKMETHOD, true);
	ResetPlanCache();
	ResetTempTableNamespace();
	ResetSequenceCaches();
}