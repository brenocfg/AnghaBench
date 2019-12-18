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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max98090_priv {int bclk; int lrclk; int /*<<< orphan*/  pclk; int /*<<< orphan*/  dmic_freq; scalar_t__ master; struct max98090_cdata* dai; } ;
struct max98090_cdata {int rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M98090_DHF_MASK ; 
 int /*<<< orphan*/  M98090_MODE_MASK ; 
 int /*<<< orphan*/  M98090_REG_FILTER_CONFIG ; 
 int /*<<< orphan*/  M98090_REG_INTERFACE_FORMAT ; 
 int /*<<< orphan*/  M98090_WS_MASK ; 
 int /*<<< orphan*/  max98090_configure_bclk (struct snd_soc_component*) ; 
 int /*<<< orphan*/  max98090_configure_dmic (struct max98090_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int max98090_dai_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *params,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	struct max98090_cdata *cdata;

	cdata = &max98090->dai[0];
	max98090->bclk = snd_soc_params_to_bclk(params);
	if (params_channels(params) == 1)
		max98090->bclk *= 2;

	max98090->lrclk = params_rate(params);

	switch (params_width(params)) {
	case 16:
		snd_soc_component_update_bits(component, M98090_REG_INTERFACE_FORMAT,
			M98090_WS_MASK, 0);
		break;
	default:
		return -EINVAL;
	}

	if (max98090->master)
		max98090_configure_bclk(component);

	cdata->rate = max98090->lrclk;

	/* Update filter mode */
	if (max98090->lrclk < 24000)
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, 0);
	else
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_MODE_MASK, M98090_MODE_MASK);

	/* Update sample rate mode */
	if (max98090->lrclk < 50000)
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, 0);
	else
		snd_soc_component_update_bits(component, M98090_REG_FILTER_CONFIG,
			M98090_DHF_MASK, M98090_DHF_MASK);

	max98090_configure_dmic(max98090, max98090->dmic_freq, max98090->pclk,
				max98090->lrclk);

	return 0;
}