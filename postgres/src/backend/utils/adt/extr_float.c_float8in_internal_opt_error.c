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
 int ERANGE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 double HUGE_VAL ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int errno ; 
 double get_float8_infinity () ; 
 double get_float8_nan () ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ pg_strncasecmp (char*,char*,int) ; 
 char* pstrdup (char*) ; 
 double strtod (char*,char**) ; 

double
float8in_internal_opt_error(char *num, char **endptr_p,
							const char *type_name, const char *orig_string,
							bool *have_error)
{
	double		val;
	char	   *endptr;

	if (have_error)
		*have_error = false;

	/* skip leading whitespace */
	while (*num != '\0' && isspace((unsigned char) *num))
		num++;

	/*
	 * Check for an empty-string input to begin with, to avoid the vagaries of
	 * strtod() on different platforms.
	 */
	if (*num == '\0')
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
							  errmsg("invalid input syntax for type %s: \"%s\"",
									 type_name, orig_string))),
					 have_error);

	errno = 0;
	val = strtod(num, &endptr);

	/* did we not see anything that looks like a double? */
	if (endptr == num || errno != 0)
	{
		int			save_errno = errno;

		/*
		 * C99 requires that strtod() accept NaN, [+-]Infinity, and [+-]Inf,
		 * but not all platforms support all of these (and some accept them
		 * but set ERANGE anyway...)  Therefore, we check for these inputs
		 * ourselves if strtod() fails.
		 *
		 * Note: C99 also requires hexadecimal input as well as some extended
		 * forms of NaN, but we consider these forms unportable and don't try
		 * to support them.  You can use 'em if your strtod() takes 'em.
		 */
		if (pg_strncasecmp(num, "NaN", 3) == 0)
		{
			val = get_float8_nan();
			endptr = num + 3;
		}
		else if (pg_strncasecmp(num, "Infinity", 8) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 8;
		}
		else if (pg_strncasecmp(num, "+Infinity", 9) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 9;
		}
		else if (pg_strncasecmp(num, "-Infinity", 9) == 0)
		{
			val = -get_float8_infinity();
			endptr = num + 9;
		}
		else if (pg_strncasecmp(num, "inf", 3) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 3;
		}
		else if (pg_strncasecmp(num, "+inf", 4) == 0)
		{
			val = get_float8_infinity();
			endptr = num + 4;
		}
		else if (pg_strncasecmp(num, "-inf", 4) == 0)
		{
			val = -get_float8_infinity();
			endptr = num + 4;
		}
		else if (save_errno == ERANGE)
		{
			/*
			 * Some platforms return ERANGE for denormalized numbers (those
			 * that are not zero, but are too close to zero to have full
			 * precision).  We'd prefer not to throw error for that, so try to
			 * detect whether it's a "real" out-of-range condition by checking
			 * to see if the result is zero or huge.
			 *
			 * On error, we intentionally complain about double precision not
			 * the given type name, and we print only the part of the string
			 * that is the current number.
			 */
			if (val == 0.0 || val >= HUGE_VAL || val <= -HUGE_VAL)
			{
				char	   *errnumber = pstrdup(num);

				errnumber[endptr - num] = '\0';
				RETURN_ERROR(ereport(ERROR,
									 (errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
									  errmsg("\"%s\" is out of range for type double precision",
											 errnumber))),
							 have_error);
			}
		}
		else
			RETURN_ERROR(ereport(ERROR,
								 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
								  errmsg("invalid input syntax for type "
										 "%s: \"%s\"",
										 type_name, orig_string))),
						 have_error);
	}
#ifdef HAVE_BUGGY_SOLARIS_STRTOD
	else
	{
		/*
		 * Many versions of Solaris have a bug wherein strtod sets endptr to
		 * point one byte beyond the end of the string when given "inf" or
		 * "infinity".
		 */
		if (endptr != num && endptr[-1] == '\0')
			endptr--;
	}
#endif							/* HAVE_BUGGY_SOLARIS_STRTOD */

	/* skip trailing whitespace */
	while (*endptr != '\0' && isspace((unsigned char) *endptr))
		endptr++;

	/* report stopping point if wanted, else complain if not end of string */
	if (endptr_p)
		*endptr_p = endptr;
	else if (*endptr != '\0')
		RETURN_ERROR(ereport(ERROR,
							 (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
							  errmsg("invalid input syntax for type "
									 "%s: \"%s\"",
									 type_name, orig_string))),
					 have_error);

	return val;
}