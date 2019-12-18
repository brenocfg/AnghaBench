#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sign; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */
 int INT_MAX ; 
 scalar_t__ NUMERIC_NEG ; 
 scalar_t__ NUMERIC_POS ; 
 int /*<<< orphan*/  PGTYPES_NUM_BAD_NUMERIC ; 
 int cmp_abs (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 

int
PGTYPESnumeric_cmp(numeric *var1, numeric *var2)
{
	/* use cmp_abs function to calculate the result */

	/* both are positive: normal comparison with cmp_abs */
	if (var1->sign == NUMERIC_POS && var2->sign == NUMERIC_POS)
		return cmp_abs(var1, var2);

	/* both are negative: return the inverse of the normal comparison */
	if (var1->sign == NUMERIC_NEG && var2->sign == NUMERIC_NEG)
	{
		/*
		 * instead of inverting the result, we invert the parameter ordering
		 */
		return cmp_abs(var2, var1);
	}

	/* one is positive, one is negative: trivial */
	if (var1->sign == NUMERIC_POS && var2->sign == NUMERIC_NEG)
		return 1;
	if (var1->sign == NUMERIC_NEG && var2->sign == NUMERIC_POS)
		return -1;

	errno = PGTYPES_NUM_BAD_NUMERIC;
	return INT_MAX;

}