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
typedef  int zic_t ;

/* Variables and functions */
 int DAYSPERWEEK ; 
 int HOURSPERDAY ; 
 int MINSPERHOUR ; 
 int SECSPERMIN ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static int
stringoffset(char *result, zic_t offset)
{
	int			hours;
	int			minutes;
	int			seconds;
	bool		negative = offset < 0;
	int			len = negative;

	if (negative)
	{
		offset = -offset;
		result[0] = '-';
	}
	seconds = offset % SECSPERMIN;
	offset /= SECSPERMIN;
	minutes = offset % MINSPERHOUR;
	offset /= MINSPERHOUR;
	hours = offset;
	if (hours >= HOURSPERDAY * DAYSPERWEEK)
	{
		result[0] = '\0';
		return 0;
	}
	len += sprintf(result + len, "%d", hours);
	if (minutes != 0 || seconds != 0)
	{
		len += sprintf(result + len, ":%02d", minutes);
		if (seconds != 0)
			len += sprintf(result + len, ":%02d", seconds);
	}
	return len;
}