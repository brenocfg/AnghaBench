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
struct rx51_device_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  channel_temp; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int INT_MAX ; 
 int INT_MIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int rx51_battery_read_adc (int /*<<< orphan*/ ) ; 
 int* rx51_temp_table1 ; 
 int* rx51_temp_table2 ; 
 int rx51_temp_table2_first ; 

__attribute__((used)) static int rx51_battery_read_temperature(struct rx51_device_info *di)
{
	int min = 0;
	int max = ARRAY_SIZE(rx51_temp_table2) - 1;
	int raw = rx51_battery_read_adc(di->channel_temp);

	if (raw < 0)
		dev_err(di->dev, "Could not read ADC: %d\n", raw);

	/* Zero and negative values are undefined */
	if (raw <= 0)
		return INT_MAX;

	/* ADC channels are 10 bit, higher value are undefined */
	if (raw >= (1 << 10))
		return INT_MIN;

	/* First check for temperature in first direct table */
	if (raw < ARRAY_SIZE(rx51_temp_table1))
		return rx51_temp_table1[raw] * 10;

	/* Binary search RAW value in second inverse table */
	while (max - min > 1) {
		int mid = (max + min) / 2;
		if (rx51_temp_table2[mid] <= raw)
			min = mid;
		else if (rx51_temp_table2[mid] > raw)
			max = mid;
		if (rx51_temp_table2[mid] == raw)
			break;
	}

	return (rx51_temp_table2_first - min) * 10;
}