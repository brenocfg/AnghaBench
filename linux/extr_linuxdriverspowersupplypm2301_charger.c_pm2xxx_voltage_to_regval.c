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
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int* pm2xxx_charger_voltage_map ; 

__attribute__((used)) static int pm2xxx_voltage_to_regval(int curr)
{
	int i;

	if (curr < pm2xxx_charger_voltage_map[0])
		return 0;

	for (i = 1; i < ARRAY_SIZE(pm2xxx_charger_voltage_map); i++) {
		if (curr < pm2xxx_charger_voltage_map[i])
			return i - 1;
	}

	i = ARRAY_SIZE(pm2xxx_charger_voltage_map) - 1;
	if (curr == pm2xxx_charger_voltage_map[i])
		return i;
	else
		return -EINVAL;
}