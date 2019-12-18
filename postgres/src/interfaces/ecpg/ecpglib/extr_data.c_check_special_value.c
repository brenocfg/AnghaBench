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
 double get_float8_infinity () ; 
 double get_float8_nan () ; 
 scalar_t__ pg_strncasecmp (char*,char*,int) ; 

__attribute__((used)) static bool
check_special_value(char *ptr, double *retval, char **endptr)
{
	if (pg_strncasecmp(ptr, "NaN", 3) == 0)
	{
		*retval = get_float8_nan();
		*endptr = ptr + 3;
		return true;
	}
	else if (pg_strncasecmp(ptr, "Infinity", 8) == 0)
	{
		*retval = get_float8_infinity();
		*endptr = ptr + 8;
		return true;
	}
	else if (pg_strncasecmp(ptr, "-Infinity", 9) == 0)
	{
		*retval = -get_float8_infinity();
		*endptr = ptr + 9;
		return true;
	}

	return false;
}