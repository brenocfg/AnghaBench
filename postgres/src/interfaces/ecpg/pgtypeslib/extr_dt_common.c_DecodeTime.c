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
struct tm {int tm_min; int tm_sec; void* tm_hour; } ;
typedef  scalar_t__ fsec_t ;

/* Variables and functions */
 int DTK_TIME_M ; 
 scalar_t__ USECS_PER_SEC ; 
 void* strtoint (char*,char**,int) ; 

int
DecodeTime(char *str, int *tmask, struct tm *tm, fsec_t *fsec)
{
	char	   *cp;

	*tmask = DTK_TIME_M;

	tm->tm_hour = strtoint(str, &cp, 10);
	if (*cp != ':')
		return -1;
	str = cp + 1;
	tm->tm_min = strtoint(str, &cp, 10);
	if (*cp == '\0')
	{
		tm->tm_sec = 0;
		*fsec = 0;
	}
	else if (*cp != ':')
		return -1;
	else
	{
		str = cp + 1;
		tm->tm_sec = strtoint(str, &cp, 10);
		if (*cp == '\0')
			*fsec = 0;
		else if (*cp == '.')
		{
			char		fstr[7];
			int			i;

			cp++;

			/*
			 * OK, we have at most six digits to care about. Let's construct a
			 * string with those digits, zero-padded on the right, and then do
			 * the conversion to an integer.
			 *
			 * XXX This truncates the seventh digit, unlike rounding it as the
			 * backend does.
			 */
			for (i = 0; i < 6; i++)
				fstr[i] = *cp != '\0' ? *cp++ : '0';
			fstr[i] = '\0';
			*fsec = strtoint(fstr, &cp, 10);
			if (*cp != '\0')
				return -1;
		}
		else
			return -1;
	}

	/* do a sanity check */
	if (tm->tm_hour < 0 || tm->tm_min < 0 || tm->tm_min > 59 ||
		tm->tm_sec < 0 || tm->tm_sec > 59 || *fsec >= USECS_PER_SEC)
		return -1;

	return 0;
}