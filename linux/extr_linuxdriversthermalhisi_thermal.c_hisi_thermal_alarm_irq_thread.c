#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hisi_thermal_sensor {int thres_temp; int /*<<< orphan*/  tzd; } ;
struct hisi_thermal_data {TYPE_1__* pdev; struct hisi_thermal_sensor sensor; int /*<<< orphan*/  (* irq_handler ) (struct hisi_thermal_data*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  hisi_thermal_get_temp (struct hisi_thermal_data*,int*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_thermal_data*) ; 
 int /*<<< orphan*/  thermal_zone_device_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t hisi_thermal_alarm_irq_thread(int irq, void *dev)
{
	struct hisi_thermal_data *data = dev;
	struct hisi_thermal_sensor *sensor = &data->sensor;
	int temp = 0;

	data->irq_handler(data);

	hisi_thermal_get_temp(data, &temp);

	if (temp >= sensor->thres_temp) {
		dev_crit(&data->pdev->dev, "THERMAL ALARM: %d > %d\n",
			 temp, sensor->thres_temp);

		thermal_zone_device_update(data->sensor.tzd,
					   THERMAL_EVENT_UNSPECIFIED);

	} else {
		dev_crit(&data->pdev->dev, "THERMAL ALARM stopped: %d < %d\n",
			 temp, sensor->thres_temp);
	}

	return IRQ_HANDLED;
}