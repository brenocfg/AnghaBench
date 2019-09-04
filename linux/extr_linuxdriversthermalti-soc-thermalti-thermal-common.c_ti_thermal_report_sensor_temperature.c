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
struct ti_thermal_data {int /*<<< orphan*/  thermal_wq; } ;
struct ti_bandgap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct ti_thermal_data* ti_bandgap_get_sensor_data (struct ti_bandgap*,int) ; 

int ti_thermal_report_sensor_temperature(struct ti_bandgap *bgp, int id)
{
	struct ti_thermal_data *data;

	data = ti_bandgap_get_sensor_data(bgp, id);

	schedule_work(&data->thermal_wq);

	return 0;
}