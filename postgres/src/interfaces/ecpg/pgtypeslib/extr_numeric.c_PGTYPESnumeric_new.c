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
 scalar_t__ alloc_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ pgtypes_alloc (int) ; 

numeric *
PGTYPESnumeric_new(void)
{
	numeric    *var;

	if ((var = (numeric *) pgtypes_alloc(sizeof(numeric))) == NULL)
		return NULL;

	if (alloc_var(var, 0) < 0)
	{
		free(var);
		return NULL;
	}

	return var;
}