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
struct pg_tm {void* tm_hour; void* tm_min; void* tm_sec; void* tm_year; void* tm_mon; void* tm_mday; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int DTERR_BAD_FORMAT ; 
 int DTK_DATE ; 
 int DTK_DATE_M ; 
 int DTK_TIME ; 
 int DTK_TIME_M ; 
 void* atoi (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  rint (double) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 double strtod (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
DecodeNumberField(int len, char *str, int fmask,
				  int *tmask, struct pg_tm *tm, fsec_t *fsec, bool *is2digits)
{
	char	   *cp;

	/*
	 * Have a decimal point? Then this is a date or something with a seconds
	 * field...
	 */
	if ((cp = strchr(str, '.')) != NULL)
	{
		/*
		 * Can we use ParseFractionalSecond here?  Not clear whether trailing
		 * junk should be rejected ...
		 */
		double		frac;

		errno = 0;
		frac = strtod(cp, NULL);
		if (errno != 0)
			return DTERR_BAD_FORMAT;
		*fsec = rint(frac * 1000000);
		/* Now truncate off the fraction for further processing */
		*cp = '\0';
		len = strlen(str);
	}
	/* No decimal point and no complete date yet? */
	else if ((fmask & DTK_DATE_M) != DTK_DATE_M)
	{
		if (len >= 6)
		{
			*tmask = DTK_DATE_M;

			/*
			 * Start from end and consider first 2 as Day, next 2 as Month,
			 * and the rest as Year.
			 */
			tm->tm_mday = atoi(str + (len - 2));
			*(str + (len - 2)) = '\0';
			tm->tm_mon = atoi(str + (len - 4));
			*(str + (len - 4)) = '\0';
			tm->tm_year = atoi(str);
			if ((len - 4) == 2)
				*is2digits = true;

			return DTK_DATE;
		}
	}

	/* not all time fields are specified? */
	if ((fmask & DTK_TIME_M) != DTK_TIME_M)
	{
		/* hhmmss */
		if (len == 6)
		{
			*tmask = DTK_TIME_M;
			tm->tm_sec = atoi(str + 4);
			*(str + 4) = '\0';
			tm->tm_min = atoi(str + 2);
			*(str + 2) = '\0';
			tm->tm_hour = atoi(str);

			return DTK_TIME;
		}
		/* hhmm? */
		else if (len == 4)
		{
			*tmask = DTK_TIME_M;
			tm->tm_sec = 0;
			tm->tm_min = atoi(str + 2);
			*(str + 2) = '\0';
			tm->tm_hour = atoi(str);

			return DTK_TIME;
		}
	}

	return DTERR_BAD_FORMAT;
}