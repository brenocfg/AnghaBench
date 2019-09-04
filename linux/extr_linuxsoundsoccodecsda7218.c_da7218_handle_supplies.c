#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct regulator {int dummy; } ;
struct da7218_priv {TYPE_1__* supplies; } ;
struct TYPE_3__ {struct regulator* consumer; int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7218_IO_CTRL ; 
 int /*<<< orphan*/  DA7218_IO_VOLTAGE_LEVEL_1_5V_2_5V ; 
 int /*<<< orphan*/  DA7218_IO_VOLTAGE_LEVEL_2_5V_3_6V ; 
 int DA7218_NUM_SUPPLIES ; 
 size_t DA7218_SUPPLY_VDDIO ; 
 int /*<<< orphan*/  DA7218_SYSTEM_ACTIVE ; 
 int /*<<< orphan*/  DA7218_SYSTEM_ACTIVE_MASK ; 
 int /*<<< orphan*/ * da7218_supply_names ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int devm_regulator_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int regulator_bulk_enable (int,TYPE_1__*) ; 
 int regulator_get_voltage (struct regulator*) ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da7218_handle_supplies(struct snd_soc_component *component)
{
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);
	struct regulator *vddio;
	u8 io_voltage_lvl = DA7218_IO_VOLTAGE_LEVEL_2_5V_3_6V;
	int i, ret;

	/* Get required supplies */
	for (i = 0; i < DA7218_NUM_SUPPLIES; ++i)
		da7218->supplies[i].supply = da7218_supply_names[i];

	ret = devm_regulator_bulk_get(component->dev, DA7218_NUM_SUPPLIES,
				      da7218->supplies);
	if (ret) {
		dev_err(component->dev, "Failed to get supplies\n");
		return ret;
	}

	/* Determine VDDIO voltage provided */
	vddio = da7218->supplies[DA7218_SUPPLY_VDDIO].consumer;
	ret = regulator_get_voltage(vddio);
	if (ret < 1500000)
		dev_warn(component->dev, "Invalid VDDIO voltage\n");
	else if (ret < 2500000)
		io_voltage_lvl = DA7218_IO_VOLTAGE_LEVEL_1_5V_2_5V;

	/* Enable main supplies */
	ret = regulator_bulk_enable(DA7218_NUM_SUPPLIES, da7218->supplies);
	if (ret) {
		dev_err(component->dev, "Failed to enable supplies\n");
		return ret;
	}

	/* Ensure device in active mode */
	snd_soc_component_write(component, DA7218_SYSTEM_ACTIVE, DA7218_SYSTEM_ACTIVE_MASK);

	/* Update IO voltage level range */
	snd_soc_component_write(component, DA7218_IO_CTRL, io_voltage_lvl);

	return 0;
}