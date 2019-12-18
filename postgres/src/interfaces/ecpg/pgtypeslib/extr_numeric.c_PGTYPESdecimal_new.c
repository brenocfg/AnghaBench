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
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pgtypes_alloc (int) ; 

decimal *
PGTYPESdecimal_new(void)
{
	decimal    *var;

	if ((var = (decimal *) pgtypes_alloc(sizeof(decimal))) == NULL)
		return NULL;

	memset(var, 0, sizeof(decimal));

	return var;
}