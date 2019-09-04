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
typedef  unsigned int u32 ;
struct thermal_zone_device {int /*<<< orphan*/  device; struct imx_thermal_data* devdata; } ;
struct thermal_soc_data {unsigned int temp_valid_mask; unsigned int temp_value_mask; unsigned int temp_value_shift; scalar_t__ version; int /*<<< orphan*/  power_down_mask; scalar_t__ sensor_ctrl; int /*<<< orphan*/  measure_temp_mask; int /*<<< orphan*/  temp_data; } ;
struct regmap {int dummy; } ;
struct imx_thermal_data {scalar_t__ mode; unsigned int c1; unsigned int c2; int alarm_temp; int temp_passive; int temp_critical; int last_temp; int irq_enabled; int /*<<< orphan*/  irq; struct thermal_soc_data* socdata; struct regmap* tempmon; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ REG_CLR ; 
 scalar_t__ REG_SET ; 
 scalar_t__ TEMPMON_IMX6Q ; 
 scalar_t__ TEMPMON_IMX7D ; 
 scalar_t__ THERMAL_DEVICE_ENABLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_set_alarm_temp (struct imx_thermal_data*,int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int imx_get_temp(struct thermal_zone_device *tz, int *temp)
{
	struct imx_thermal_data *data = tz->devdata;
	const struct thermal_soc_data *soc_data = data->socdata;
	struct regmap *map = data->tempmon;
	unsigned int n_meas;
	bool wait;
	u32 val;

	if (data->mode == THERMAL_DEVICE_ENABLED) {
		/* Check if a measurement is currently in progress */
		regmap_read(map, soc_data->temp_data, &val);
		wait = !(val & soc_data->temp_valid_mask);
	} else {
		/*
		 * Every time we measure the temperature, we will power on the
		 * temperature sensor, enable measurements, take a reading,
		 * disable measurements, power off the temperature sensor.
		 */
		regmap_write(map, soc_data->sensor_ctrl + REG_CLR,
			    soc_data->power_down_mask);
		regmap_write(map, soc_data->sensor_ctrl + REG_SET,
			    soc_data->measure_temp_mask);

		wait = true;
	}

	/*
	 * According to the temp sensor designers, it may require up to ~17us
	 * to complete a measurement.
	 */
	if (wait)
		usleep_range(20, 50);

	regmap_read(map, soc_data->temp_data, &val);

	if (data->mode != THERMAL_DEVICE_ENABLED) {
		regmap_write(map, soc_data->sensor_ctrl + REG_CLR,
			     soc_data->measure_temp_mask);
		regmap_write(map, soc_data->sensor_ctrl + REG_SET,
			     soc_data->power_down_mask);
	}

	if ((val & soc_data->temp_valid_mask) == 0) {
		dev_dbg(&tz->device, "temp measurement never finished\n");
		return -EAGAIN;
	}

	n_meas = (val & soc_data->temp_value_mask)
		>> soc_data->temp_value_shift;

	/* See imx_init_calib() for formula derivation */
	if (data->socdata->version == TEMPMON_IMX7D)
		*temp = (n_meas - data->c1 + 25) * 1000;
	else
		*temp = data->c2 - n_meas * data->c1;

	/* Update alarm value to next higher trip point for TEMPMON_IMX6Q */
	if (data->socdata->version == TEMPMON_IMX6Q) {
		if (data->alarm_temp == data->temp_passive &&
			*temp >= data->temp_passive)
			imx_set_alarm_temp(data, data->temp_critical);
		if (data->alarm_temp == data->temp_critical &&
			*temp < data->temp_passive) {
			imx_set_alarm_temp(data, data->temp_passive);
			dev_dbg(&tz->device, "thermal alarm off: T < %d\n",
				data->alarm_temp / 1000);
		}
	}

	if (*temp != data->last_temp) {
		dev_dbg(&tz->device, "millicelsius: %d\n", *temp);
		data->last_temp = *temp;
	}

	/* Reenable alarm IRQ if temperature below alarm temperature */
	if (!data->irq_enabled && *temp < data->alarm_temp) {
		data->irq_enabled = true;
		enable_irq(data->irq);
	}

	return 0;
}