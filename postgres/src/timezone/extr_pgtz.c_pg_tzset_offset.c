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
typedef  int /*<<< orphan*/  tzname ;
typedef  int /*<<< orphan*/  pg_tz ;
typedef  int /*<<< orphan*/  offsetstr ;

/* Variables and functions */
 long SECS_PER_HOUR ; 
 long SECS_PER_MINUTE ; 
 int /*<<< orphan*/ * pg_tzset (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

pg_tz *
pg_tzset_offset(long gmtoffset)
{
	long		absoffset = (gmtoffset < 0) ? -gmtoffset : gmtoffset;
	char		offsetstr[64];
	char		tzname[128];

	snprintf(offsetstr, sizeof(offsetstr),
			 "%02ld", absoffset / SECS_PER_HOUR);
	absoffset %= SECS_PER_HOUR;
	if (absoffset != 0)
	{
		snprintf(offsetstr + strlen(offsetstr),
				 sizeof(offsetstr) - strlen(offsetstr),
				 ":%02ld", absoffset / SECS_PER_MINUTE);
		absoffset %= SECS_PER_MINUTE;
		if (absoffset != 0)
			snprintf(offsetstr + strlen(offsetstr),
					 sizeof(offsetstr) - strlen(offsetstr),
					 ":%02ld", absoffset);
	}
	if (gmtoffset > 0)
		snprintf(tzname, sizeof(tzname), "<-%s>+%s",
				 offsetstr, offsetstr);
	else
		snprintf(tzname, sizeof(tzname), "<+%s>-%s",
				 offsetstr, offsetstr);

	return pg_tzset(tzname);
}