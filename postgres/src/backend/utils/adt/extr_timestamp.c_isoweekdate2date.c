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
 int isoweek2j (int,int) ; 
 int /*<<< orphan*/  j2date (int,int*,int*,int*) ; 

void
isoweekdate2date(int isoweek, int wday, int *year, int *mon, int *mday)
{
	int			jday;

	jday = isoweek2j(*year, isoweek);
	/* convert Gregorian week start (Sunday=1) to ISO week start (Monday=1) */
	if (wday > 1)
		jday += wday - 2;
	else
		jday += 6;
	j2date(jday, year, mon, mday);
}