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
#define  DTZ 129 
 int DecodeSpecial (scalar_t__,char*,int*) ; 
 scalar_t__ DecodeTimezone (char*,int*) ; 
 scalar_t__ MAXDATEFIELDS ; 
#define  TZ 128 
 scalar_t__ isalpha (unsigned char) ; 

__attribute__((used)) static int
DecodePosixTimezone(char *str, int *tzp)
{
	int			val,
				tz;
	int			type;
	char	   *cp;
	char		delim;

	cp = str;
	while (*cp != '\0' && isalpha((unsigned char) *cp))
		cp++;

	if (DecodeTimezone(cp, &tz) != 0)
		return -1;

	delim = *cp;
	*cp = '\0';
	type = DecodeSpecial(MAXDATEFIELDS - 1, str, &val);
	*cp = delim;

	switch (type)
	{
		case DTZ:
		case TZ:
			*tzp = -(val + tz);
			break;

		default:
			return -1;
	}

	return 0;
}