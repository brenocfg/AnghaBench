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
struct twl6040_data {int pll; unsigned int clk_in; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TWL6040_SYSCLK_SEL_HPPLL 129 
#define  TWL6040_SYSCLK_SEL_LPPLL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int twl6040_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case TWL6040_SYSCLK_SEL_LPPLL:
	case TWL6040_SYSCLK_SEL_HPPLL:
		priv->pll = clk_id;
		priv->clk_in = freq;
		break;
	default:
		dev_err(component->dev, "unknown clk_id %d\n", clk_id);
		return -EINVAL;
	}

	return 0;
}