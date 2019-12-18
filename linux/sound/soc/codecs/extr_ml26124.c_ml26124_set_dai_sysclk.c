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
struct ml26124_priv {int clk_in; unsigned int mclk; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ML26124_USE_MCLKI 129 
#define  ML26124_USE_PLLOUT 128 
 struct ml26124_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ml26124_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case ML26124_USE_PLLOUT:
		priv->clk_in = ML26124_USE_PLLOUT;
		break;
	case ML26124_USE_MCLKI:
		priv->clk_in = ML26124_USE_MCLKI;
		break;
	default:
		return -EINVAL;
	}

	priv->mclk = freq;

	return 0;
}