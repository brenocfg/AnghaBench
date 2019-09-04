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
struct ibm_thermal_sensors_struct {int* temp; } ;

/* Variables and functions */
 int TPACPI_THERMAL_SENSOR_NA ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 int thermal_get_sensors (struct ibm_thermal_sensors_struct*) ; 

__attribute__((used)) static void thermal_dump_all_sensors(void)
{
	int n, i;
	struct ibm_thermal_sensors_struct t;

	n = thermal_get_sensors(&t);
	if (n <= 0)
		return;

	pr_notice("temperatures (Celsius):");

	for (i = 0; i < n; i++) {
		if (t.temp[i] != TPACPI_THERMAL_SENSOR_NA)
			pr_cont(" %d", (int)(t.temp[i] / 1000));
		else
			pr_cont(" N/A");
	}

	pr_cont("\n");
}