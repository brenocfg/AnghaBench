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
struct platform_device {int dummy; } ;
struct hisi_thermal_sensor {int dummy; } ;
struct hisi_thermal_data {int /*<<< orphan*/  (* disable_sensor ) (struct hisi_thermal_data*) ;struct hisi_thermal_sensor sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_thermal_toggle_sensor (struct hisi_thermal_sensor*,int) ; 
 struct hisi_thermal_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_thermal_data*) ; 

__attribute__((used)) static int hisi_thermal_remove(struct platform_device *pdev)
{
	struct hisi_thermal_data *data = platform_get_drvdata(pdev);
	struct hisi_thermal_sensor *sensor = &data->sensor;

	hisi_thermal_toggle_sensor(sensor, false);

	data->disable_sensor(data);

	return 0;
}