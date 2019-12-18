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
struct pg_tm {int tm_mon; } ;
typedef  int /*<<< orphan*/  fsec_t ;

/* Variables and functions */
 int DOY ; 
 int DTERR_BAD_FORMAT ; 
 int DTK_DATE_M ; 
 int DTK_M (int) ; 
 int DecodeNumber (int,char*,int,int,int*,struct pg_tm*,int /*<<< orphan*/ *,int*) ; 
 int DecodeSpecial (int,char*,int*) ; 
 int IGNORE_DTF ; 
 int MAXDATEFIELDS ; 
#define  MONTH 128 
 int TZ ; 
 int /*<<< orphan*/  isalnum (unsigned char) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
DecodeDate(char *str, int fmask, int *tmask, bool *is2digits,
		   struct pg_tm *tm)
{
	fsec_t		fsec;
	int			nf = 0;
	int			i,
				len;
	int			dterr;
	bool		haveTextMonth = false;
	int			type,
				val,
				dmask = 0;
	char	   *field[MAXDATEFIELDS];

	*tmask = 0;

	/* parse this string... */
	while (*str != '\0' && nf < MAXDATEFIELDS)
	{
		/* skip field separators */
		while (*str != '\0' && !isalnum((unsigned char) *str))
			str++;

		if (*str == '\0')
			return DTERR_BAD_FORMAT;	/* end of string after separator */

		field[nf] = str;
		if (isdigit((unsigned char) *str))
		{
			while (isdigit((unsigned char) *str))
				str++;
		}
		else if (isalpha((unsigned char) *str))
		{
			while (isalpha((unsigned char) *str))
				str++;
		}

		/* Just get rid of any non-digit, non-alpha characters... */
		if (*str != '\0')
			*str++ = '\0';
		nf++;
	}

	/* look first for text fields, since that will be unambiguous month */
	for (i = 0; i < nf; i++)
	{
		if (isalpha((unsigned char) *field[i]))
		{
			type = DecodeSpecial(i, field[i], &val);
			if (type == IGNORE_DTF)
				continue;

			dmask = DTK_M(type);
			switch (type)
			{
				case MONTH:
					tm->tm_mon = val;
					haveTextMonth = true;
					break;

				default:
					return DTERR_BAD_FORMAT;
			}
			if (fmask & dmask)
				return DTERR_BAD_FORMAT;

			fmask |= dmask;
			*tmask |= dmask;

			/* mark this field as being completed */
			field[i] = NULL;
		}
	}

	/* now pick up remaining numeric fields */
	for (i = 0; i < nf; i++)
	{
		if (field[i] == NULL)
			continue;

		if ((len = strlen(field[i])) <= 0)
			return DTERR_BAD_FORMAT;

		dterr = DecodeNumber(len, field[i], haveTextMonth, fmask,
							 &dmask, tm,
							 &fsec, is2digits);
		if (dterr)
			return dterr;

		if (fmask & dmask)
			return DTERR_BAD_FORMAT;

		fmask |= dmask;
		*tmask |= dmask;
	}

	if ((fmask & ~(DTK_M(DOY) | DTK_M(TZ))) != DTK_DATE_M)
		return DTERR_BAD_FORMAT;

	/* validation of the field values must wait until ValidateDate() */

	return 0;
}