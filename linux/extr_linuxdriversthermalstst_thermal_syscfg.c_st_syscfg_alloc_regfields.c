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
struct st_thermal_sensor {int /*<<< orphan*/  pwr; TYPE_1__* cdata; int /*<<< orphan*/  regmap; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * reg_fields; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 size_t TEMP_PWR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_syscfg_alloc_regfields(struct st_thermal_sensor *sensor)
{
	struct device *dev = sensor->dev;

	sensor->pwr = devm_regmap_field_alloc(dev, sensor->regmap,
					sensor->cdata->reg_fields[TEMP_PWR]);

	if (IS_ERR(sensor->pwr)) {
		dev_err(dev, "failed to alloc syscfg regfields\n");
		return PTR_ERR(sensor->pwr);
	}

	return 0;
}