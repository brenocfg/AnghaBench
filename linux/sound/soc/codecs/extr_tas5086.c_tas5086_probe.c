#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tas5086_private {int pwm_start_mid_z; int charge_period; int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct snd_soc_component {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAS5086_MASTER_VOL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas5086_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tas5086_dt_ids ; 
 int tas5086_init (TYPE_1__*,struct tas5086_private*) ; 
 int /*<<< orphan*/  tas5086_reset (struct tas5086_private*) ; 

__attribute__((used)) static int tas5086_probe(struct snd_soc_component *component)
{
	struct tas5086_private *priv = snd_soc_component_get_drvdata(component);
	int i, ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	if (ret < 0) {
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		return ret;
	}

	priv->pwm_start_mid_z = 0;
	priv->charge_period = 1300000; /* hardware default is 1300 ms */

	if (of_match_device(of_match_ptr(tas5086_dt_ids), component->dev)) {
		struct device_node *of_node = component->dev->of_node;

		of_property_read_u32(of_node, "ti,charge-period",
				     &priv->charge_period);

		for (i = 0; i < 6; i++) {
			char name[25];

			snprintf(name, sizeof(name),
				 "ti,mid-z-channel-%d", i + 1);

			if (of_get_property(of_node, name, NULL) != NULL)
				priv->pwm_start_mid_z |= 1 << i;
		}
	}

	tas5086_reset(priv);
	ret = tas5086_init(component->dev, priv);
	if (ret < 0)
		goto exit_disable_regulators;

	/* set master volume to 0 dB */
	ret = regmap_write(priv->regmap, TAS5086_MASTER_VOL, 0x30);
	if (ret < 0)
		goto exit_disable_regulators;

	return 0;

exit_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);

	return ret;
}