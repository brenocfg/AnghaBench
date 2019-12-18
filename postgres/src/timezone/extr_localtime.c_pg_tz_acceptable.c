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
struct pg_tm {scalar_t__ tm_sec; } ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int pg_time_t ;

/* Variables and functions */
 int POSTGRES_EPOCH_JDATE ; 
 int SECS_PER_DAY ; 
 int UNIX_EPOCH_JDATE ; 
 struct pg_tm* pg_localtime (int*,int /*<<< orphan*/ *) ; 

bool
pg_tz_acceptable(pg_tz *tz)
{
	struct pg_tm *tt;
	pg_time_t	time2000;

	/*
	 * To detect leap-second timekeeping, run pg_localtime for what should be
	 * GMT midnight, 2000-01-01.  Insist that the tm_sec value be zero; any
	 * other result has to be due to leap seconds.
	 */
	time2000 = (POSTGRES_EPOCH_JDATE - UNIX_EPOCH_JDATE) * SECS_PER_DAY;
	tt = pg_localtime(&time2000, tz);
	if (!tt || tt->tm_sec != 0)
		return false;

	return true;
}