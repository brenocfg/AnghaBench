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
struct snd_soc_component {int dummy; } ;
struct rt5640_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5640_DMIC ; 
 int /*<<< orphan*/  RT5640_DMIC_1_DP_GPIO3 ; 
 int /*<<< orphan*/  RT5640_DMIC_1_DP_MASK ; 
 int /*<<< orphan*/  RT5640_DMIC_2_DP_GPIO4 ; 
 int /*<<< orphan*/  RT5640_DMIC_2_DP_MASK ; 
 int /*<<< orphan*/  RT5640_GP2_PIN_DMIC1_SCL ; 
 int /*<<< orphan*/  RT5640_GP2_PIN_MASK ; 
 int /*<<< orphan*/  RT5640_GP3_PIN_DMIC1_SDA ; 
 int /*<<< orphan*/  RT5640_GP3_PIN_MASK ; 
 int /*<<< orphan*/  RT5640_GP4_PIN_DMIC2_SDA ; 
 int /*<<< orphan*/  RT5640_GP4_PIN_MASK ; 
 int /*<<< orphan*/  RT5640_GPIO_CTRL1 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rt5640_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int rt5640_dmic_enable(struct snd_soc_component *component,
		       bool dmic1_data_pin, bool dmic2_data_pin)
{
	struct rt5640_priv *rt5640 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
		RT5640_GP2_PIN_MASK, RT5640_GP2_PIN_DMIC1_SCL);

	if (dmic1_data_pin) {
		regmap_update_bits(rt5640->regmap, RT5640_DMIC,
			RT5640_DMIC_1_DP_MASK, RT5640_DMIC_1_DP_GPIO3);
		regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
			RT5640_GP3_PIN_MASK, RT5640_GP3_PIN_DMIC1_SDA);
	}

	if (dmic2_data_pin) {
		regmap_update_bits(rt5640->regmap, RT5640_DMIC,
			RT5640_DMIC_2_DP_MASK, RT5640_DMIC_2_DP_GPIO4);
		regmap_update_bits(rt5640->regmap, RT5640_GPIO_CTRL1,
			RT5640_GP4_PIN_MASK, RT5640_GP4_PIN_DMIC2_SDA);
	}

	return 0;
}