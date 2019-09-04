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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cs43130_private {scalar_t__ xtal_ibias; int /*<<< orphan*/  supplies; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  wq; int /*<<< orphan*/  work; scalar_t__ dc_meas; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CS43130_HP_PLUG_INT ; 
 int CS43130_HP_UNPLUG_INT ; 
 int /*<<< orphan*/  CS43130_INT_MASK_1 ; 
 int /*<<< orphan*/  CS43130_NUM_SUPPLIES ; 
 int CS43130_XTAL_ERR_INT ; 
 int CS43130_XTAL_ERR_INT_SHIFT ; 
 scalar_t__ CS43130_XTAL_UNUSED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_hpload_ac_l ; 
 int /*<<< orphan*/  dev_attr_hpload_ac_r ; 
 int /*<<< orphan*/  dev_attr_hpload_dc_l ; 
 int /*<<< orphan*/  dev_attr_hpload_dc_r ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs43130_private* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs43130_i2c_remove(struct i2c_client *client)
{
	struct cs43130_private *cs43130 = i2c_get_clientdata(client);

	if (cs43130->xtal_ibias != CS43130_XTAL_UNUSED)
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_XTAL_ERR_INT,
				   1 << CS43130_XTAL_ERR_INT_SHIFT);

	regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
			   CS43130_HP_PLUG_INT | CS43130_HP_UNPLUG_INT,
			   CS43130_HP_PLUG_INT | CS43130_HP_UNPLUG_INT);

	if (cs43130->dc_meas) {
		cancel_work_sync(&cs43130->work);
		flush_workqueue(cs43130->wq);

		device_remove_file(&client->dev, &dev_attr_hpload_dc_l);
		device_remove_file(&client->dev, &dev_attr_hpload_dc_r);
		device_remove_file(&client->dev, &dev_attr_hpload_ac_l);
		device_remove_file(&client->dev, &dev_attr_hpload_ac_r);
	}

	gpiod_set_value_cansleep(cs43130->reset_gpio, 0);

	pm_runtime_disable(&client->dev);
	regulator_bulk_disable(CS43130_NUM_SUPPLIES, cs43130->supplies);

	return 0;
}