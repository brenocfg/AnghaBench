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
 int MINSPERHOUR ; 
 int SECSPERMIN ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char const *
abbroffset(char *buf, zic_t offset)
{
	char		sign = '+';
	int			seconds,
				minutes;

	if (offset < 0)
	{
		offset = -offset;
		sign = '-';
	}

	seconds = offset % SECSPERMIN;
	offset /= SECSPERMIN;
	minutes = offset % MINSPERHOUR;
	offset /= MINSPERHOUR;
	if (100 <= offset)
	{
		error(_("%%z UT offset magnitude exceeds 99:59:59"));
		return "%z";
	}
	else
	{
		char	   *p = buf;

		*p++ = sign;
		*p++ = '0' + offset / 10;
		*p++ = '0' + offset % 10;
		if (minutes | seconds)
		{
			*p++ = '0' + minutes / 10;
			*p++ = '0' + minutes % 10;
			if (seconds)
			{
				*p++ = '0' + seconds / 10;
				*p++ = '0' + seconds % 10;
			}
		}
		*p = '\0';
		return buf;
	}
}