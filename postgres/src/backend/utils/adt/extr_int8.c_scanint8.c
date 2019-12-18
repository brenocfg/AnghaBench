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
typedef  int /*<<< orphan*/  int8 ;
typedef  int /*<<< orphan*/  int64 ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  PG_INT64_MIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,char const*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int pg_mul_s64_overflow (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int pg_sub_s64_overflow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

bool
scanint8(const char *str, bool errorOK, int64 *result)
{
	const char *ptr = str;
	int64		tmp = 0;
	bool		neg = false;

	/*
	 * Do our own scan, rather than relying on sscanf which might be broken
	 * for long long.
	 *
	 * As INT64_MIN can't be stored as a positive 64 bit integer, accumulate
	 * value as a negative number.
	 */

	/* skip leading spaces */
	while (*ptr && isspace((unsigned char) *ptr))
		ptr++;

	/* handle sign */
	if (*ptr == '-')
	{
		ptr++;
		neg = true;
	}
	else if (*ptr == '+')
		ptr++;

	/* require at least one digit */
	if (unlikely(!isdigit((unsigned char) *ptr)))
		goto invalid_syntax;

	/* process digits */
	while (*ptr && isdigit((unsigned char) *ptr))
	{
		int8		digit = (*ptr++ - '0');

		if (unlikely(pg_mul_s64_overflow(tmp, 10, &tmp)) ||
			unlikely(pg_sub_s64_overflow(tmp, digit, &tmp)))
			goto out_of_range;
	}

	/* allow trailing whitespace, but not other trailing chars */
	while (*ptr != '\0' && isspace((unsigned char) *ptr))
		ptr++;

	if (unlikely(*ptr != '\0'))
		goto invalid_syntax;

	if (!neg)
	{
		/* could fail if input is most negative number */
		if (unlikely(tmp == PG_INT64_MIN))
			goto out_of_range;
		tmp = -tmp;
	}

	*result = tmp;
	return true;

out_of_range:
	if (!errorOK)
		ereport(ERROR,
				(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
				 errmsg("value \"%s\" is out of range for type %s",
						str, "bigint")));
	return false;

invalid_syntax:
	if (!errorOK)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"bigint", str)));
	return false;
}