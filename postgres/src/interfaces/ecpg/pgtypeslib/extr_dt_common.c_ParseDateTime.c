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
 int DTK_DATE ; 
 int DTK_NUMBER ; 
 int DTK_SPECIAL ; 
 int DTK_STRING ; 
 int DTK_TIME ; 
 int DTK_TZ ; 
 int MAXDATEFIELDS ; 
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ ispunct (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 void* pg_tolower (unsigned char) ; 

int
ParseDateTime(char *timestr, char *lowstr,
			  char **field, int *ftype, int *numfields, char **endstr)
{
	int			nf = 0;
	char	   *lp = lowstr;

	*endstr = timestr;
	/* outer loop through fields */
	while (*(*endstr) != '\0')
	{
		/* Record start of current field */
		if (nf >= MAXDATEFIELDS)
			return -1;
		field[nf] = lp;

		/* leading digit? then date or time */
		if (isdigit((unsigned char) *(*endstr)))
		{
			*lp++ = *(*endstr)++;
			while (isdigit((unsigned char) *(*endstr)))
				*lp++ = *(*endstr)++;

			/* time field? */
			if (*(*endstr) == ':')
			{
				ftype[nf] = DTK_TIME;
				*lp++ = *(*endstr)++;
				while (isdigit((unsigned char) *(*endstr)) ||
					   (*(*endstr) == ':') || (*(*endstr) == '.'))
					*lp++ = *(*endstr)++;
			}
			/* date field? allow embedded text month */
			else if (*(*endstr) == '-' || *(*endstr) == '/' || *(*endstr) == '.')
			{
				/* save delimiting character to use later */
				char	   *dp = (*endstr);

				*lp++ = *(*endstr)++;
				/* second field is all digits? then no embedded text month */
				if (isdigit((unsigned char) *(*endstr)))
				{
					ftype[nf] = (*dp == '.') ? DTK_NUMBER : DTK_DATE;
					while (isdigit((unsigned char) *(*endstr)))
						*lp++ = *(*endstr)++;

					/*
					 * insist that the delimiters match to get a three-field
					 * date.
					 */
					if (*(*endstr) == *dp)
					{
						ftype[nf] = DTK_DATE;
						*lp++ = *(*endstr)++;
						while (isdigit((unsigned char) *(*endstr)) || (*(*endstr) == *dp))
							*lp++ = *(*endstr)++;
					}
				}
				else
				{
					ftype[nf] = DTK_DATE;
					while (isalnum((unsigned char) *(*endstr)) || (*(*endstr) == *dp))
						*lp++ = pg_tolower((unsigned char) *(*endstr)++);
				}
			}

			/*
			 * otherwise, number only and will determine year, month, day, or
			 * concatenated fields later...
			 */
			else
				ftype[nf] = DTK_NUMBER;
		}
		/* Leading decimal point? Then fractional seconds... */
		else if (*(*endstr) == '.')
		{
			*lp++ = *(*endstr)++;
			while (isdigit((unsigned char) *(*endstr)))
				*lp++ = *(*endstr)++;

			ftype[nf] = DTK_NUMBER;
		}

		/*
		 * text? then date string, month, day of week, special, or timezone
		 */
		else if (isalpha((unsigned char) *(*endstr)))
		{
			ftype[nf] = DTK_STRING;
			*lp++ = pg_tolower((unsigned char) *(*endstr)++);
			while (isalpha((unsigned char) *(*endstr)))
				*lp++ = pg_tolower((unsigned char) *(*endstr)++);

			/*
			 * Full date string with leading text month? Could also be a POSIX
			 * time zone...
			 */
			if (*(*endstr) == '-' || *(*endstr) == '/' || *(*endstr) == '.')
			{
				char	   *dp = (*endstr);

				ftype[nf] = DTK_DATE;
				*lp++ = *(*endstr)++;
				while (isdigit((unsigned char) *(*endstr)) || *(*endstr) == *dp)
					*lp++ = *(*endstr)++;
			}
		}
		/* skip leading spaces */
		else if (isspace((unsigned char) *(*endstr)))
		{
			(*endstr)++;
			continue;
		}
		/* sign? then special or numeric timezone */
		else if (*(*endstr) == '+' || *(*endstr) == '-')
		{
			*lp++ = *(*endstr)++;
			/* soak up leading whitespace */
			while (isspace((unsigned char) *(*endstr)))
				(*endstr)++;
			/* numeric timezone? */
			if (isdigit((unsigned char) *(*endstr)))
			{
				ftype[nf] = DTK_TZ;
				*lp++ = *(*endstr)++;
				while (isdigit((unsigned char) *(*endstr)) ||
					   (*(*endstr) == ':') || (*(*endstr) == '.'))
					*lp++ = *(*endstr)++;
			}
			/* special? */
			else if (isalpha((unsigned char) *(*endstr)))
			{
				ftype[nf] = DTK_SPECIAL;
				*lp++ = pg_tolower((unsigned char) *(*endstr)++);
				while (isalpha((unsigned char) *(*endstr)))
					*lp++ = pg_tolower((unsigned char) *(*endstr)++);
			}
			/* otherwise something wrong... */
			else
				return -1;
		}
		/* ignore punctuation but use as delimiter */
		else if (ispunct((unsigned char) *(*endstr)))
		{
			(*endstr)++;
			continue;

		}
		/* otherwise, something is not right... */
		else
			return -1;

		/* force in a delimiter after each field */
		*lp++ = '\0';
		nf++;
	}

	*numfields = nf;

	return 0;
}