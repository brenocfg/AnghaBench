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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  AbortOutOfAnyTransaction () ; 
 int /*<<< orphan*/  LockReleaseAll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USER_LOCKMETHOD ; 

__attribute__((used)) static void
ShutdownPostgres(int code, Datum arg)
{
	/* Make sure we've killed any active transaction */
	AbortOutOfAnyTransaction();

	/*
	 * User locks are not released by transaction end, so be sure to release
	 * them explicitly.
	 */
	LockReleaseAll(USER_LOCKMETHOD, true);
}