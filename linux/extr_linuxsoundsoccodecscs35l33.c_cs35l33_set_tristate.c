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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct cs35l33_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_CLK_CTL ; 
 int /*<<< orphan*/  CS35L33_PWRCTL2 ; 
 int /*<<< orphan*/  CS35L33_SDOUT_3ST_I2S ; 
 int /*<<< orphan*/  CS35L33_SDOUT_3ST_TDM ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l33_set_tristate(struct snd_soc_dai *dai, int tristate)
{
	struct snd_soc_component *component = dai->component;
	struct cs35l33_private *priv = snd_soc_component_get_drvdata(component);

	if (tristate) {
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
			CS35L33_SDOUT_3ST_I2S, CS35L33_SDOUT_3ST_I2S);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
			CS35L33_SDOUT_3ST_TDM, CS35L33_SDOUT_3ST_TDM);
	} else {
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
			CS35L33_SDOUT_3ST_I2S, 0);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
			CS35L33_SDOUT_3ST_TDM, 0);
	}

	return 0;
}