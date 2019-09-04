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
 int /*<<< orphan*/  WDRTAS_THERMAL_SENSOR ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int rtas_get_sensor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int wdrtas_get_temperature(void)
{
	int result;
	int temperature = 0;

	result = rtas_get_sensor(WDRTAS_THERMAL_SENSOR, 0, &temperature);

	if (result < 0)
		pr_warn("reading the thermal sensor failed: %i\n", result);
	else
		temperature = ((temperature * 9) / 5) + 32; /* fahrenheit */

	return temperature;
}