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
struct i_sabre_codec_priv {int fmt; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBS_CFS 128 
 int SND_SOC_DAIFMT_MASTER_MASK ; 
 int i_sabre_codec_dai_startup_slave (struct snd_pcm_substream*,struct snd_soc_dai*) ; 
 struct i_sabre_codec_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int i_sabre_codec_dai_startup(
		struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	struct snd_soc_component      *component = dai->component;
	struct i_sabre_codec_priv *i_sabre_codec
					= snd_soc_component_get_drvdata(component);

	switch (i_sabre_codec->fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		return i_sabre_codec_dai_startup_slave(substream, dai);

	default:
		return (-EINVAL);
	}
}