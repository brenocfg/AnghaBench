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
struct thermal_zone_device {scalar_t__ passive_delay; scalar_t__ polling_delay; struct imx_thermal_data* devdata; } ;
struct thermal_soc_data {int /*<<< orphan*/  power_down_mask; scalar_t__ sensor_ctrl; int /*<<< orphan*/  measure_temp_mask; } ;
struct regmap {int dummy; } ;
struct imx_thermal_data {int irq_enabled; int mode; int /*<<< orphan*/  irq; struct thermal_soc_data* socdata; struct regmap* tempmon; } ;
typedef  enum thermal_device_mode { ____Placeholder_thermal_device_mode } thermal_device_mode ;

/* Variables and functions */
 scalar_t__ IMX_PASSIVE_DELAY ; 
 scalar_t__ IMX_POLLING_DELAY ; 
 scalar_t__ REG_CLR ; 
 scalar_t__ REG_SET ; 
 int THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  THERMAL_EVENT_UNSPECIFIED ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_zone_device_update (struct thermal_zone_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_set_mode(struct thermal_zone_device *tz,
			enum thermal_device_mode mode)
{
	struct imx_thermal_data *data = tz->devdata;
	struct regmap *map = data->tempmon;
	const struct thermal_soc_data *soc_data = data->socdata;

	if (mode == THERMAL_DEVICE_ENABLED) {
		tz->polling_delay = IMX_POLLING_DELAY;
		tz->passive_delay = IMX_PASSIVE_DELAY;

		regmap_write(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->power_down_mask);
		regmap_write(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->measure_temp_mask);

		if (!data->irq_enabled) {
			data->irq_enabled = true;
			enable_irq(data->irq);
		}
	} else {
		regmap_write(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->measure_temp_mask);
		regmap_write(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->power_down_mask);

		tz->polling_delay = 0;
		tz->passive_delay = 0;

		if (data->irq_enabled) {
			disable_irq(data->irq);
			data->irq_enabled = false;
		}
	}

	data->mode = mode;
	thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	return 0;
}