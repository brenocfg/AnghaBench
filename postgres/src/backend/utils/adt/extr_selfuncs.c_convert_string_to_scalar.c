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
 double convert_one_string_to_scalar (char*,int,int) ; 

__attribute__((used)) static void
convert_string_to_scalar(char *value,
						 double *scaledvalue,
						 char *lobound,
						 double *scaledlobound,
						 char *hibound,
						 double *scaledhibound)
{
	int			rangelo,
				rangehi;
	char	   *sptr;

	rangelo = rangehi = (unsigned char) hibound[0];
	for (sptr = lobound; *sptr; sptr++)
	{
		if (rangelo > (unsigned char) *sptr)
			rangelo = (unsigned char) *sptr;
		if (rangehi < (unsigned char) *sptr)
			rangehi = (unsigned char) *sptr;
	}
	for (sptr = hibound; *sptr; sptr++)
	{
		if (rangelo > (unsigned char) *sptr)
			rangelo = (unsigned char) *sptr;
		if (rangehi < (unsigned char) *sptr)
			rangehi = (unsigned char) *sptr;
	}
	/* If range includes any upper-case ASCII chars, make it include all */
	if (rangelo <= 'Z' && rangehi >= 'A')
	{
		if (rangelo > 'A')
			rangelo = 'A';
		if (rangehi < 'Z')
			rangehi = 'Z';
	}
	/* Ditto lower-case */
	if (rangelo <= 'z' && rangehi >= 'a')
	{
		if (rangelo > 'a')
			rangelo = 'a';
		if (rangehi < 'z')
			rangehi = 'z';
	}
	/* Ditto digits */
	if (rangelo <= '9' && rangehi >= '0')
	{
		if (rangelo > '0')
			rangelo = '0';
		if (rangehi < '9')
			rangehi = '9';
	}

	/*
	 * If range includes less than 10 chars, assume we have not got enough
	 * data, and make it include regular ASCII set.
	 */
	if (rangehi - rangelo < 9)
	{
		rangelo = ' ';
		rangehi = 127;
	}

	/*
	 * Now strip any common prefix of the three strings.
	 */
	while (*lobound)
	{
		if (*lobound != *hibound || *lobound != *value)
			break;
		lobound++, hibound++, value++;
	}

	/*
	 * Now we can do the conversions.
	 */
	*scaledvalue = convert_one_string_to_scalar(value, rangelo, rangehi);
	*scaledlobound = convert_one_string_to_scalar(lobound, rangelo, rangehi);
	*scaledhibound = convert_one_string_to_scalar(hibound, rangelo, rangehi);
}