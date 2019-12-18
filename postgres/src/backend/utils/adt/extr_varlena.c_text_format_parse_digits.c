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
typedef  char int8 ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE_PARSE_POINTER (char const*,char const*) ; 
 int /*<<< orphan*/  ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_add_s32_overflow (int,char,int*) ; 
 int /*<<< orphan*/  pg_mul_s32_overflow (int,int,int*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
text_format_parse_digits(const char **ptr, const char *end_ptr, int *value)
{
	bool		found = false;
	const char *cp = *ptr;
	int			val = 0;

	while (*cp >= '0' && *cp <= '9')
	{
		int8		digit = (*cp - '0');

		if (unlikely(pg_mul_s32_overflow(val, 10, &val)) ||
			unlikely(pg_add_s32_overflow(val, digit, &val)))
			ereport(ERROR,
					(errcode(ERRCODE_NUMERIC_VALUE_OUT_OF_RANGE),
					 errmsg("number is out of range")));
		ADVANCE_PARSE_POINTER(cp, end_ptr);
		found = true;
	}

	*ptr = cp;
	*value = val;

	return found;
}