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
typedef  int /*<<< orphan*/  numeric ;

/* Variables and functions */
 int /*<<< orphan*/  PGTYPESnumeric_free (int /*<<< orphan*/ *) ; 
 scalar_t__ pgtypes_alloc (int) ; 
 int set_var_from_str (char*,char**,int /*<<< orphan*/ *) ; 

numeric *
PGTYPESnumeric_from_asc(char *str, char **endptr)
{
	numeric    *value = (numeric *) pgtypes_alloc(sizeof(numeric));
	int			ret;

	char	   *realptr;
	char	  **ptr = (endptr != NULL) ? endptr : &realptr;

	if (!value)
		return NULL;

	ret = set_var_from_str(str, ptr, value);
	if (ret)
	{
		PGTYPESnumeric_free(value);
		return NULL;
	}

	return value;
}