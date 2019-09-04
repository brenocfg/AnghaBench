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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct ak4104_private {int /*<<< orphan*/  regulator; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AK4104_CONTROL1_PW ; 
 int AK4104_CONTROL1_RSTN ; 
 int /*<<< orphan*/  AK4104_REG_CONTROL1 ; 
 int /*<<< orphan*/  AK4104_REG_TX ; 
 int AK4104_TX_TXE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 struct ak4104_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4104_probe(struct snd_soc_component *component)
{
	struct ak4104_private *ak4104 = snd_soc_component_get_drvdata(component);
	int ret;

	ret = regulator_enable(ak4104->regulator);
	if (ret < 0) {
		dev_err(component->dev, "Unable to enable regulator: %d\n", ret);
		return ret;
	}

	/* set power-up and non-reset bits */
	ret = regmap_update_bits(ak4104->regmap, AK4104_REG_CONTROL1,
				 AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN,
				 AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN);
	if (ret < 0)
		goto exit_disable_regulator;

	/* enable transmitter */
	ret = regmap_update_bits(ak4104->regmap, AK4104_REG_TX,
				 AK4104_TX_TXE, AK4104_TX_TXE);
	if (ret < 0)
		goto exit_disable_regulator;

	return 0;

exit_disable_regulator:
	regulator_disable(ak4104->regulator);
	return ret;
}