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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct aic3x_priv {int slot_width; scalar_t__ dai_fmt; int tdm_delay; } ;
struct TYPE_2__ {int sample_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC3X_ASD_INTF_CTRLC ; 
 scalar_t__ SND_SOC_DAIFMT_DSP_A ; 
 scalar_t__ SND_SOC_DAIFMT_DSP_B ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aic3x_prepare(struct snd_pcm_substream *substream,
			 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	int delay = 0;
	int width = aic3x->slot_width;

	if (!width)
		width = substream->runtime->sample_bits;

	/* TDM slot selection only valid in DSP_A/_B mode */
	if (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		delay += (aic3x->tdm_delay*width + 1);
	else if (aic3x->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		delay += aic3x->tdm_delay*width;

	/* Configure data delay */
	snd_soc_component_write(component, AIC3X_ASD_INTF_CTRLC, delay);

	return 0;
}