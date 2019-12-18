#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int digits; char sign; char* val_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int getRightMostDot (char const*) ; 
 int initValue (long) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strchr (char const*,int) ; 
 size_t strlen (char const*) ; 
 TYPE_1__ value ; 

int
rfmtlong(long lng_val, const char *fmt, char *outbuf)
{
	size_t		fmt_len = strlen(fmt);
	size_t		temp_len;
	int			i,
				j,				/* position in temp */
				k,
				dotpos;
	int			leftalign = 0,
				blank = 0,
				sign = 0,
				entitydone = 0,
				signdone = 0,
				brackets_ok = 0;
	char	   *temp;
	char		tmp[2] = " ";
	char		lastfmt = ' ',
				fmtchar = ' ';

	temp = (char *) malloc(fmt_len + 1);
	if (!temp)
	{
		errno = ENOMEM;
		return -1;
	}

	/* put all info about the long in a struct */
	if (initValue(lng_val) == -1)
	{
		free(temp);
		errno = ENOMEM;
		return -1;
	}

	/* '<' is the only format, where we have to align left */
	if (strchr(fmt, (int) '<'))
		leftalign = 1;

	/* '(' requires ')' */
	if (strchr(fmt, (int) '(') && strchr(fmt, (int) ')'))
		brackets_ok = 1;

	/* get position of the right-most dot in the format-string */
	/* and fill the temp-string wit '0's up to there. */
	dotpos = getRightMostDot(fmt);

	/* start to parse the format-string */
	temp[0] = '\0';
	k = value.digits - 1;		/* position in the value_string */
	for (i = fmt_len - 1, j = 0; i >= 0; i--, j++)
	{
		/* qualify, where we are in the value_string */
		if (k < 0)
		{
			blank = 1;
			if (k == -1)
				sign = 1;
			if (leftalign)
			{
				/* can't use strncat(,,0) here, Solaris would freak out */
				if (sign)
					if (signdone)
					{
						temp[j] = '\0';
						break;
					}
			}
		}
		/* if we're right side of the right-most dot, print '0' */
		if (dotpos >= 0 && dotpos <= i)
		{
			if (dotpos < i)
			{
				if (fmt[i] == ')')
					tmp[0] = value.sign == '-' ? ')' : ' ';
				else
					tmp[0] = '0';
			}
			else
				tmp[0] = '.';
			strcat(temp, tmp);
			continue;
		}
		/* the ',' needs special attention, if it is in the blank area */
		if (blank && fmt[i] == ',')
			fmtchar = lastfmt;
		else
			fmtchar = fmt[i];
		/* waiting for the sign */
		if (k < 0 && leftalign && sign && !signdone && fmtchar != '+' && fmtchar != '-')
			continue;
		/* analyse this format-char */
		switch (fmtchar)
		{
			case ',':
				tmp[0] = ',';
				k++;
				break;
			case '*':
				if (blank)
					tmp[0] = '*';
				else
					tmp[0] = value.val_string[k];
				break;
			case '&':
				if (blank)
					tmp[0] = '0';
				else
					tmp[0] = value.val_string[k];
				break;
			case '#':
				if (blank)
					tmp[0] = ' ';
				else
					tmp[0] = value.val_string[k];
				break;
			case '-':
				if (sign && value.sign == '-' && !signdone)
				{
					tmp[0] = '-';
					signdone = 1;
				}
				else if (blank)
					tmp[0] = ' ';
				else
					tmp[0] = value.val_string[k];
				break;
			case '+':
				if (sign && !signdone)
				{
					tmp[0] = value.sign;
					signdone = 1;
				}
				else if (blank)
					tmp[0] = ' ';
				else
					tmp[0] = value.val_string[k];
				break;
			case '(':
				if (sign && brackets_ok && value.sign == '-')
					tmp[0] = '(';
				else if (blank)
					tmp[0] = ' ';
				else
					tmp[0] = value.val_string[k];
				break;
			case ')':
				if (brackets_ok && value.sign == '-')
					tmp[0] = ')';
				else
					tmp[0] = ' ';
				break;
			case '$':
				if (blank && !entitydone)
				{
					tmp[0] = '$';
					entitydone = 1;
				}
				else if (blank)
					tmp[0] = ' ';
				else
					tmp[0] = value.val_string[k];
				break;
			case '<':
				tmp[0] = value.val_string[k];
				break;
			default:
				tmp[0] = fmt[i];
		}
		strcat(temp, tmp);
		lastfmt = fmt[i];
		k--;
	}
	/* safety-net */
	temp[fmt_len] = '\0';

	/* reverse the temp-string and put it into the outbuf */
	temp_len = strlen(temp);
	outbuf[0] = '\0';
	for (i = temp_len - 1; i >= 0; i--)
	{
		tmp[0] = temp[i];
		strcat(outbuf, tmp);
	}
	outbuf[temp_len] = '\0';

	/* cleaning up */
	free(temp);
	free(value.val_string);

	return 0;
}