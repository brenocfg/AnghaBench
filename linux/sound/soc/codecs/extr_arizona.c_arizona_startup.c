#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct arizona_priv {unsigned int sysclk; unsigned int asyncclk; struct arizona_dai_priv* dai; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;
struct arizona_dai_priv {int clk; TYPE_1__ constraint; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_44K1_RATE_MASK ; 
 int /*<<< orphan*/  ARIZONA_48K_RATE_MASK ; 
#define  ARIZONA_CLK_ASYNCCLK 129 
#define  ARIZONA_CLK_SYSCLK 128 
 int /*<<< orphan*/  ARIZONA_RATE_MASK ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int arizona_startup(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	struct arizona_dai_priv *dai_priv = &priv->dai[dai->id - 1];
	unsigned int base_rate;

	if (!substream->runtime)
		return 0;

	switch (dai_priv->clk) {
	case ARIZONA_CLK_SYSCLK:
		base_rate = priv->sysclk;
		break;
	case ARIZONA_CLK_ASYNCCLK:
		base_rate = priv->asyncclk;
		break;
	default:
		return 0;
	}

	if (base_rate == 0)
		dai_priv->constraint.mask = ARIZONA_RATE_MASK;
	else if (base_rate % 8000)
		dai_priv->constraint.mask = ARIZONA_44K1_RATE_MASK;
	else
		dai_priv->constraint.mask = ARIZONA_48K_RATE_MASK;

	return snd_pcm_hw_constraint_list(substream->runtime, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &dai_priv->constraint);
}