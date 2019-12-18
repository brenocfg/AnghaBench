#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rscale; int dscale; int weight; long* digits; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ numeric ;

/* Variables and functions */
 int LONG_MAX ; 
 int /*<<< orphan*/  NUMERIC_NEG ; 
 int /*<<< orphan*/  NUMERIC_POS ; 
 scalar_t__ alloc_var (TYPE_1__*,int) ; 

int
PGTYPESnumeric_from_long(signed long int long_val, numeric *var)
{
	/* calculate the size of the long int number */
	/* a number n needs log_10 n digits */

	/*
	 * however we multiply by 10 each time and compare instead of calculating
	 * the logarithm
	 */

	int			size = 0;
	int			i;
	signed long int abs_long_val = long_val;
	signed long int extract;
	signed long int reach_limit;

	if (abs_long_val < 0)
	{
		abs_long_val *= -1;
		var->sign = NUMERIC_NEG;
	}
	else
		var->sign = NUMERIC_POS;

	reach_limit = 1;
	do
	{
		size++;
		reach_limit *= 10;
	} while (reach_limit - 1 < abs_long_val && reach_limit <= LONG_MAX / 10);

	if (reach_limit > LONG_MAX / 10)
	{
		/* add the first digit and a .0 */
		size += 2;
	}
	else
	{
		/* always add a .0 */
		size++;
		reach_limit /= 10;
	}

	if (alloc_var(var, size) < 0)
		return -1;

	var->rscale = 1;
	var->dscale = 1;
	var->weight = size - 2;

	i = 0;
	do
	{
		extract = abs_long_val - (abs_long_val % reach_limit);
		var->digits[i] = extract / reach_limit;
		abs_long_val -= extract;
		i++;
		reach_limit /= 10;

		/*
		 * we can abandon if abs_long_val reaches 0, because the memory is
		 * initialized properly and filled with '0', so converting 10000 in
		 * only one step is no problem
		 */
	} while (abs_long_val > 0);

	return 0;
}