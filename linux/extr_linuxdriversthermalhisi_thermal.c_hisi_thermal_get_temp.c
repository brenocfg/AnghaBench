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
struct hisi_thermal_sensor {int /*<<< orphan*/  thres_temp; int /*<<< orphan*/  id; } ;
struct hisi_thermal_data {int (* get_temp ) (struct hisi_thermal_data*) ;TYPE_1__* pdev; struct hisi_thermal_sensor sensor; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct hisi_thermal_data*) ; 

__attribute__((used)) static int hisi_thermal_get_temp(void *__data, int *temp)
{
	struct hisi_thermal_data *data = __data;
	struct hisi_thermal_sensor *sensor = &data->sensor;

	*temp = data->get_temp(data);

	dev_dbg(&data->pdev->dev, "id=%d, temp=%d, thres=%d\n",
		sensor->id, *temp, sensor->thres_temp);

	return 0;
}