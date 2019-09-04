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
struct st_thermal_sensor {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; TYPE_1__* cdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  sys_compat; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_compatible (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_syscfg_regmap_init(struct st_thermal_sensor *sensor)
{
	sensor->regmap =
		syscon_regmap_lookup_by_compatible(sensor->cdata->sys_compat);
	if (IS_ERR(sensor->regmap)) {
		dev_err(sensor->dev, "failed to find syscfg regmap\n");
		return PTR_ERR(sensor->regmap);
	}

	return 0;
}