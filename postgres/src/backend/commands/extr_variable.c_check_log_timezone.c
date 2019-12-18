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
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  GUC_check_errdetail (char*) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*,char*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  pg_tz_acceptable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pg_tzset (char*) ; 

bool
check_log_timezone(char **newval, void **extra, GucSource source)
{
	pg_tz	   *new_tz;

	/*
	 * Assume it is a timezone name, and try to load it.
	 */
	new_tz = pg_tzset(*newval);

	if (!new_tz)
	{
		/* Doesn't seem to be any great value in errdetail here */
		return false;
	}

	if (!pg_tz_acceptable(new_tz))
	{
		GUC_check_errmsg("time zone \"%s\" appears to use leap seconds",
						 *newval);
		GUC_check_errdetail("PostgreSQL does not support leap seconds.");
		return false;
	}

	/*
	 * Pass back data for assign_log_timezone to use
	 */
	*extra = malloc(sizeof(pg_tz *));
	if (!*extra)
		return false;
	*((pg_tz **) *extra) = new_tz;

	return true;
}