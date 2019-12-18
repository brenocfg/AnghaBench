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
struct TYPE_4__ {char* unit; int base_unit; double multiplier; } ;
typedef  TYPE_1__ unit_conversion ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int GUC_UNIT_MEMORY ; 
 int fabs (double) ; 
 TYPE_1__* memory_unit_conversion_table ; 
 double rint (double) ; 
 TYPE_1__* time_unit_conversion_table ; 

__attribute__((used)) static void
convert_real_from_base_unit(double base_value, int base_unit,
							double *value, const char **unit)
{
	const unit_conversion *table;
	int			i;

	*unit = NULL;

	if (base_unit & GUC_UNIT_MEMORY)
		table = memory_unit_conversion_table;
	else
		table = time_unit_conversion_table;

	for (i = 0; *table[i].unit; i++)
	{
		if (base_unit == table[i].base_unit)
		{
			/*
			 * Accept the first conversion that divides the value evenly; or
			 * if there is none, use the smallest (last) target unit.
			 *
			 * What we actually care about here is whether snprintf with "%g"
			 * will print the value as an integer, so the obvious test of
			 * "*value == rint(*value)" is too strict; roundoff error might
			 * make us choose an unreasonably small unit.  As a compromise,
			 * accept a divisor that is within 1e-8 of producing an integer.
			 */
			*value = base_value / table[i].multiplier;
			*unit = table[i].unit;
			if (*value > 0 &&
				fabs((rint(*value) / *value) - 1.0) <= 1e-8)
				break;
		}
	}

	Assert(*unit != NULL);
}