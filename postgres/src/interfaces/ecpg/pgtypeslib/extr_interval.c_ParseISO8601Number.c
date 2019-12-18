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
 int DTERR_FIELD_OVERFLOW ; 
 double INT_MAX ; 
 double INT_MIN ; 
 scalar_t__ errno ; 
 scalar_t__ floor (double) ; 
 scalar_t__ isdigit (unsigned char) ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static int
ParseISO8601Number(const char *str, char **endptr, int *ipart, double *fpart)
{
	double		val;

	if (!(isdigit((unsigned char) *str) || *str == '-' || *str == '.'))
		return DTERR_BAD_FORMAT;
	errno = 0;
	val = strtod(str, endptr);
	/* did we not see anything that looks like a double? */
	if (*endptr == str || errno != 0)
		return DTERR_BAD_FORMAT;
	/* watch out for overflow */
	if (val < INT_MIN || val > INT_MAX)
		return DTERR_FIELD_OVERFLOW;
	/* be very sure we truncate towards zero (cf dtrunc()) */
	if (val >= 0)
		*ipart = (int) floor(val);
	else
		*ipart = (int) -floor(-val);
	*fpart = val - *ipart;
	return 0;
}