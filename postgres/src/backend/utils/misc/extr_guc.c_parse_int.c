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
 scalar_t__ ERANGE ; 
 int GUC_UNIT ; 
 int GUC_UNIT_MEMORY ; 
 double INT_MAX ; 
 double INT_MIN ; 
 int /*<<< orphan*/  convert_to_base_unit (double,char*,int,double*) ; 
 scalar_t__ errno ; 
 char* gettext_noop (char*) ; 
 scalar_t__ isnan (double) ; 
 scalar_t__ isspace (unsigned char) ; 
 char* memory_units_hint ; 
 double rint (double) ; 
 double strtod (char const*,char**) ; 
 double strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 char* time_units_hint ; 

bool
parse_int(const char *value, int *result, int flags, const char **hintmsg)
{
	/*
	 * We assume here that double is wide enough to represent any integer
	 * value with adequate precision.
	 */
	double		val;
	char	   *endptr;

	/* To suppress compiler warnings, always set output params */
	if (result)
		*result = 0;
	if (hintmsg)
		*hintmsg = NULL;

	/*
	 * Try to parse as an integer (allowing octal or hex input).  If the
	 * conversion stops at a decimal point or 'e', or overflows, re-parse as
	 * float.  This should work fine as long as we have no unit names starting
	 * with 'e'.  If we ever do, the test could be extended to check for a
	 * sign or digit after 'e', but for now that's unnecessary.
	 */
	errno = 0;
	val = strtol(value, &endptr, 0);
	if (*endptr == '.' || *endptr == 'e' || *endptr == 'E' ||
		errno == ERANGE)
	{
		errno = 0;
		val = strtod(value, &endptr);
	}

	if (endptr == value || errno == ERANGE)
		return false;			/* no HINT for these cases */

	/* reject NaN (infinities will fail range check below) */
	if (isnan(val))
		return false;			/* treat same as syntax error; no HINT */

	/* allow whitespace between number and unit */
	while (isspace((unsigned char) *endptr))
		endptr++;

	/* Handle possible unit */
	if (*endptr != '\0')
	{
		if ((flags & GUC_UNIT) == 0)
			return false;		/* this setting does not accept a unit */

		if (!convert_to_base_unit(val,
								  endptr, (flags & GUC_UNIT),
								  &val))
		{
			/* invalid unit, or garbage after the unit; set hint and fail. */
			if (hintmsg)
			{
				if (flags & GUC_UNIT_MEMORY)
					*hintmsg = memory_units_hint;
				else
					*hintmsg = time_units_hint;
			}
			return false;
		}
	}

	/* Round to int, then check for overflow */
	val = rint(val);

	if (val > INT_MAX || val < INT_MIN)
	{
		if (hintmsg)
			*hintmsg = gettext_noop("Value exceeds integer range.");
		return false;
	}

	if (result)
		*result = (int) val;
	return true;
}