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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {unsigned int* list; int count; } ;
struct es8316_priv {unsigned int sysclk; unsigned int* allowed_rates; TYPE_1__ sysclk_constraints; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int NR_SUPPORTED_MCLK_LRCK_RATIOS ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 struct es8316_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int* supported_mclk_lrck_ratios ; 

__attribute__((used)) static int es8316_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct es8316_priv *es8316 = snd_soc_component_get_drvdata(component);
	int i, ret;
	int count = 0;

	es8316->sysclk = freq;

	if (freq == 0) {
		es8316->sysclk_constraints.list = NULL;
		es8316->sysclk_constraints.count = 0;

		return 0;
	}

	ret = clk_set_rate(es8316->mclk, freq);
	if (ret)
		return ret;

	/* Limit supported sample rates to ones that can be autodetected
	 * by the codec running in slave mode.
	 */
	for (i = 0; i < NR_SUPPORTED_MCLK_LRCK_RATIOS; i++) {
		const unsigned int ratio = supported_mclk_lrck_ratios[i];

		if (freq % ratio == 0)
			es8316->allowed_rates[count++] = freq / ratio;
	}

	es8316->sysclk_constraints.list = es8316->allowed_rates;
	es8316->sysclk_constraints.count = count;

	return 0;
}