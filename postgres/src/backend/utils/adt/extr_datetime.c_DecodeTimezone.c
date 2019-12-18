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
 int DTERR_BAD_FORMAT ; 
 int DTERR_TZDISP_OVERFLOW ; 
 scalar_t__ ERANGE ; 
 int MAX_TZDISP_HOUR ; 
 int MINS_PER_HOUR ; 
 int SECS_PER_MINUTE ; 
 scalar_t__ errno ; 
 int strlen (char*) ; 
 int strtoint (char*,char**,int) ; 

int
DecodeTimezone(char *str, int *tzp)
{
	int			tz;
	int			hr,
				min,
				sec = 0;
	char	   *cp;

	/* leading character must be "+" or "-" */
	if (*str != '+' && *str != '-')
		return DTERR_BAD_FORMAT;

	errno = 0;
	hr = strtoint(str + 1, &cp, 10);
	if (errno == ERANGE)
		return DTERR_TZDISP_OVERFLOW;

	/* explicit delimiter? */
	if (*cp == ':')
	{
		errno = 0;
		min = strtoint(cp + 1, &cp, 10);
		if (errno == ERANGE)
			return DTERR_TZDISP_OVERFLOW;
		if (*cp == ':')
		{
			errno = 0;
			sec = strtoint(cp + 1, &cp, 10);
			if (errno == ERANGE)
				return DTERR_TZDISP_OVERFLOW;
		}
	}
	/* otherwise, might have run things together... */
	else if (*cp == '\0' && strlen(str) > 3)
	{
		min = hr % 100;
		hr = hr / 100;
		/* we could, but don't, support a run-together hhmmss format */
	}
	else
		min = 0;

	/* Range-check the values; see notes in datatype/timestamp.h */
	if (hr < 0 || hr > MAX_TZDISP_HOUR)
		return DTERR_TZDISP_OVERFLOW;
	if (min < 0 || min >= MINS_PER_HOUR)
		return DTERR_TZDISP_OVERFLOW;
	if (sec < 0 || sec >= SECS_PER_MINUTE)
		return DTERR_TZDISP_OVERFLOW;

	tz = (hr * MINS_PER_HOUR + min) * SECS_PER_MINUTE + sec;
	if (*str == '-')
		tz = -tz;

	*tzp = -tz;

	if (*cp != '\0')
		return DTERR_BAD_FORMAT;

	return 0;
}