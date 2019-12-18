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
struct tm {int tm_mon; void* tm_hour; void* tm_min; void* tm_sec; void* tm_year; void* tm_mday; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int DTK_DATE ; 
 int DTK_DATE_M ; 
 int DTK_TIME ; 
 int DTK_TIME_M ; 
 void* atoi (char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strtoint (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
DecodeNumberField(int len, char *str, int fmask,
				  int *tmask, struct tm *tm, fsec_t *fsec, bool *is2digits)
{
	char	   *cp;

	/*
	 * Have a decimal point? Then this is a date or something with a seconds
	 * field...
	 */
	if ((cp = strchr(str, '.')) != NULL)
	{
		char		fstr[7];
		int			i;

		cp++;

		/*
		 * OK, we have at most six digits to care about. Let's construct a
		 * string with those digits, zero-padded on the right, and then do the
		 * conversion to an integer.
		 *
		 * XXX This truncates the seventh digit, unlike rounding it as the
		 * backend does.
		 */
		for (i = 0; i < 6; i++)
			fstr[i] = *cp != '\0' ? *cp++ : '0';
		fstr[i] = '\0';
		*fsec = strtoint(fstr, NULL, 10);
		*cp = '\0';
		len = strlen(str);
	}
	/* No decimal point and no complete date yet? */
	else if ((fmask & DTK_DATE_M) != DTK_DATE_M)
	{
		/* yyyymmdd? */
		if (len == 8)
		{
			*tmask = DTK_DATE_M;

			tm->tm_mday = atoi(str + 6);
			*(str + 6) = '\0';
			tm->tm_mon = atoi(str + 4);
			*(str + 4) = '\0';
			tm->tm_year = atoi(str + 0);

			return DTK_DATE;
		}
		/* yymmdd? */
		else if (len == 6)
		{
			*tmask = DTK_DATE_M;
			tm->tm_mday = atoi(str + 4);
			*(str + 4) = '\0';
			tm->tm_mon = atoi(str + 2);
			*(str + 2) = '\0';
			tm->tm_year = atoi(str + 0);
			*is2digits = true;

			return DTK_DATE;
		}
		/* yyddd? */
		else if (len == 5)
		{
			*tmask = DTK_DATE_M;
			tm->tm_mday = atoi(str + 2);
			*(str + 2) = '\0';
			tm->tm_mon = 1;
			tm->tm_year = atoi(str + 0);
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
			tm->tm_hour = atoi(str + 0);

			return DTK_TIME;
		}
		/* hhmm? */
		else if (len == 4)
		{
			*tmask = DTK_TIME_M;
			tm->tm_sec = 0;
			tm->tm_min = atoi(str + 2);
			*(str + 2) = '\0';
			tm->tm_hour = atoi(str + 0);

			return DTK_TIME;
		}
	}

	return -1;
}