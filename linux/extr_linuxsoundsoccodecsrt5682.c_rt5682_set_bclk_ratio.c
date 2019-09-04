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
struct snd_soc_dai {size_t id; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct rt5682_priv {unsigned int* bclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RT5682_ADDA_CLK_2 ; 
 int /*<<< orphan*/  RT5682_I2S2_BCLK_MS2_32 ; 
 int /*<<< orphan*/  RT5682_I2S2_BCLK_MS2_64 ; 
 int /*<<< orphan*/  RT5682_I2S2_BCLK_MS2_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct rt5682_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt5682_set_bclk_ratio(struct snd_soc_dai *dai, unsigned int ratio)
{
	struct snd_soc_component *component = dai->component;
	struct rt5682_priv *rt5682 = snd_soc_component_get_drvdata(component);

	rt5682->bclk[dai->id] = ratio;

	switch (ratio) {
	case 64:
		snd_soc_component_update_bits(component, RT5682_ADDA_CLK_2,
			RT5682_I2S2_BCLK_MS2_MASK,
			RT5682_I2S2_BCLK_MS2_64);
		break;
	case 32:
		snd_soc_component_update_bits(component, RT5682_ADDA_CLK_2,
			RT5682_I2S2_BCLK_MS2_MASK,
			RT5682_I2S2_BCLK_MS2_32);
		break;
	default:
		dev_err(dai->dev, "Invalid bclk ratio %d\n", ratio);
		return -EINVAL;
	}

	return 0;
}