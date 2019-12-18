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
typedef  int int64 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int GUC_UNIT_MEMORY ; 
 TYPE_1__* memory_unit_conversion_table ; 
 scalar_t__ rint (int) ; 
 TYPE_1__* time_unit_conversion_table ; 

__attribute__((used)) static void
convert_int_from_base_unit(int64 base_value, int base_unit,
						   int64 *value, const char **unit)
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
			 * Accept the first conversion that divides the value evenly.  We
			 * assume that the conversions for each base unit are ordered from
			 * greatest unit to the smallest!
			 */
			if (table[i].multiplier <= 1.0 ||
				base_value % (int64) table[i].multiplier == 0)
			{
				*value = (int64) rint(base_value / table[i].multiplier);
				*unit = table[i].unit;
				break;
			}
		}
	}

	Assert(*unit != NULL);
}