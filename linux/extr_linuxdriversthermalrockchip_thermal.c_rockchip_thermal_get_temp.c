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
struct rockchip_tsadc_chip {int (* get_temp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  table; } ;
struct rockchip_thermal_sensor {int /*<<< orphan*/  id; struct rockchip_thermal_data* thermal; } ;
struct rockchip_thermal_data {TYPE_1__* pdev; int /*<<< orphan*/  regs; struct rockchip_tsadc_chip* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rockchip_thermal_get_temp(void *_sensor, int *out_temp)
{
	struct rockchip_thermal_sensor *sensor = _sensor;
	struct rockchip_thermal_data *thermal = sensor->thermal;
	const struct rockchip_tsadc_chip *tsadc = sensor->thermal->chip;
	int retval;

	retval = tsadc->get_temp(&tsadc->table,
				 sensor->id, thermal->regs, out_temp);
	dev_dbg(&thermal->pdev->dev, "sensor %d - temp: %d, retval: %d\n",
		sensor->id, *out_temp, retval);

	return retval;
}