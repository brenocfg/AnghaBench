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
 int /*<<< orphan*/  log_timezone ; 
 int /*<<< orphan*/  pg_tzset (char*) ; 
 int /*<<< orphan*/  session_timezone ; 

void
pg_timezone_initialize(void)
{
	/*
	 * We may not yet know where PGSHAREDIR is (in particular this is true in
	 * an EXEC_BACKEND subprocess).  So use "GMT", which pg_tzset forces to be
	 * interpreted without reference to the filesystem.  This corresponds to
	 * the bootstrap default for these variables in guc.c, although in
	 * principle it could be different.
	 */
	session_timezone = pg_tzset("GMT");
	log_timezone = session_timezone;
}