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
struct max17042_platform_data {int enable_current_sense; int /*<<< orphan*/  temp_max; int /*<<< orphan*/  temp_min; int /*<<< orphan*/  vmax; int /*<<< orphan*/  vmin; int /*<<< orphan*/  num_init_data; int /*<<< orphan*/  init_data; } ;
struct max17042_chip {scalar_t__ chip_type; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX17042_DEFAULT_TEMP_MAX ; 
 int /*<<< orphan*/  MAX17042_DEFAULT_TEMP_MIN ; 
 int /*<<< orphan*/  MAX17042_DEFAULT_VMAX ; 
 int /*<<< orphan*/  MAX17042_DEFAULT_VMIN ; 
 int /*<<< orphan*/  MAX17042_MiscCFG ; 
 scalar_t__ MAXIM_DEVICE_TYPE_MAX17042 ; 
 struct max17042_platform_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max17047_default_pdata_init_regs ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static struct max17042_platform_data *
max17042_get_default_pdata(struct max17042_chip *chip)
{
	struct device *dev = &chip->client->dev;
	struct max17042_platform_data *pdata;
	int ret, misc_cfg;

	/*
	 * The MAX17047 gets used on x86 where we might not have pdata, assume
	 * the firmware will already have initialized the fuel-gauge and provide
	 * default values for the non init bits to make things work.
	 */
	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return pdata;

	if (chip->chip_type != MAXIM_DEVICE_TYPE_MAX17042) {
		pdata->init_data = max17047_default_pdata_init_regs;
		pdata->num_init_data =
			ARRAY_SIZE(max17047_default_pdata_init_regs);
	}

	ret = regmap_read(chip->regmap, MAX17042_MiscCFG, &misc_cfg);
	if (ret < 0)
		return NULL;

	/* If bits 0-1 are set to 3 then only Voltage readings are used */
	if ((misc_cfg & 0x3) == 0x3)
		pdata->enable_current_sense = false;
	else
		pdata->enable_current_sense = true;

	pdata->vmin = MAX17042_DEFAULT_VMIN;
	pdata->vmax = MAX17042_DEFAULT_VMAX;
	pdata->temp_min = MAX17042_DEFAULT_TEMP_MIN;
	pdata->temp_max = MAX17042_DEFAULT_TEMP_MAX;

	return pdata;
}