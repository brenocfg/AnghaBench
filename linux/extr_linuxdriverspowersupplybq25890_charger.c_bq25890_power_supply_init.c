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
struct power_supply_config {int /*<<< orphan*/  num_supplicants; int /*<<< orphan*/  supplied_to; struct bq25890_device* drv_data; } ;
struct bq25890_device {int /*<<< orphan*/  charger; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bq25890_charger_supplied_to ; 
 int /*<<< orphan*/  bq25890_power_supply_desc ; 
 int /*<<< orphan*/  power_supply_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct power_supply_config*) ; 

__attribute__((used)) static int bq25890_power_supply_init(struct bq25890_device *bq)
{
	struct power_supply_config psy_cfg = { .drv_data = bq, };

	psy_cfg.supplied_to = bq25890_charger_supplied_to;
	psy_cfg.num_supplicants = ARRAY_SIZE(bq25890_charger_supplied_to);

	bq->charger = power_supply_register(bq->dev, &bq25890_power_supply_desc,
					    &psy_cfg);

	return PTR_ERR_OR_ZERO(bq->charger);
}