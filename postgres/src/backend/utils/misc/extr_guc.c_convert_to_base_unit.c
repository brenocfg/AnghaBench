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
struct TYPE_4__ {int base_unit; double multiplier; scalar_t__* unit; } ;
typedef  TYPE_1__ unit_conversion ;

/* Variables and functions */
 int GUC_UNIT_MEMORY ; 
 int MAX_UNIT_LEN ; 
 scalar_t__ isspace (unsigned char) ; 
 TYPE_1__* memory_unit_conversion_table ; 
 double rint (double) ; 
 scalar_t__ strcmp (char*,scalar_t__*) ; 
 TYPE_1__* time_unit_conversion_table ; 

__attribute__((used)) static bool
convert_to_base_unit(double value, const char *unit,
					 int base_unit, double *base_value)
{
	char		unitstr[MAX_UNIT_LEN + 1];
	int			unitlen;
	const unit_conversion *table;
	int			i;

	/* extract unit string to compare to table entries */
	unitlen = 0;
	while (*unit != '\0' && !isspace((unsigned char) *unit) &&
		   unitlen < MAX_UNIT_LEN)
		unitstr[unitlen++] = *(unit++);
	unitstr[unitlen] = '\0';
	/* allow whitespace after unit */
	while (isspace((unsigned char) *unit))
		unit++;
	if (*unit != '\0')
		return false;			/* unit too long, or garbage after it */

	/* now search the appropriate table */
	if (base_unit & GUC_UNIT_MEMORY)
		table = memory_unit_conversion_table;
	else
		table = time_unit_conversion_table;

	for (i = 0; *table[i].unit; i++)
	{
		if (base_unit == table[i].base_unit &&
			strcmp(unitstr, table[i].unit) == 0)
		{
			double		cvalue = value * table[i].multiplier;

			/*
			 * If the user gave a fractional value such as "30.1GB", round it
			 * off to the nearest multiple of the next smaller unit, if there
			 * is one.
			 */
			if (*table[i + 1].unit &&
				base_unit == table[i + 1].base_unit)
				cvalue = rint(cvalue / table[i + 1].multiplier) *
					table[i + 1].multiplier;

			*base_value = cvalue;
			return true;
		}
	}
	return false;
}