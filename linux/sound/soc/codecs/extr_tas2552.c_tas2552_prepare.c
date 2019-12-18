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
struct tas2552_data {scalar_t__ dai_fmt; scalar_t__ tdm_delay; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAIFMT_DSP_A ; 
 scalar_t__ SND_SOC_DAIFMT_DSP_B ; 
 int /*<<< orphan*/  TAS2552_SER_CTRL_2 ; 
 struct tas2552_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tas2552_prepare(struct snd_pcm_substream *substream,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	int delay = 0;

	/* TDM slot selection only valid in DSP_A/_B mode */
	if (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_A)
		delay += (tas2552->tdm_delay + 1);
	else if (tas2552->dai_fmt == SND_SOC_DAIFMT_DSP_B)
		delay += tas2552->tdm_delay;

	/* Configure data delay */
	snd_soc_component_write(component, TAS2552_SER_CTRL_2, delay);

	return 0;
}