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
 double float8in_internal_opt_error (char*,char**,char const*,char const*,int /*<<< orphan*/ *) ; 

double
float8in_internal(char *num, char **endptr_p,
				  const char *type_name, const char *orig_string)
{
	return float8in_internal_opt_error(num, endptr_p, type_name,
									   orig_string, NULL);
}