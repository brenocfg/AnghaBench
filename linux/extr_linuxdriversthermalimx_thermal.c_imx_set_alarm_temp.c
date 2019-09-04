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
struct thermal_soc_data {scalar_t__ version; int high_alarm_mask; int high_alarm_shift; scalar_t__ high_alarm_ctrl; } ;
struct regmap {int dummy; } ;
struct imx_thermal_data {int alarm_temp; int c1; int c2; struct thermal_soc_data* socdata; struct regmap* tempmon; } ;

/* Variables and functions */
 scalar_t__ REG_CLR ; 
 scalar_t__ REG_SET ; 
 scalar_t__ TEMPMON_IMX7D ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int) ; 

__attribute__((used)) static void imx_set_alarm_temp(struct imx_thermal_data *data,
			       int alarm_temp)
{
	struct regmap *map = data->tempmon;
	const struct thermal_soc_data *soc_data = data->socdata;
	int alarm_value;

	data->alarm_temp = alarm_temp;

	if (data->socdata->version == TEMPMON_IMX7D)
		alarm_value = alarm_temp / 1000 + data->c1 - 25;
	else
		alarm_value = (data->c2 - alarm_temp) / data->c1;

	regmap_write(map, soc_data->high_alarm_ctrl + REG_CLR,
		     soc_data->high_alarm_mask);
	regmap_write(map, soc_data->high_alarm_ctrl + REG_SET,
		     alarm_value << soc_data->high_alarm_shift);
}