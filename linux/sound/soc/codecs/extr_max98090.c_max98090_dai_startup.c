#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {TYPE_2__* runtime; } ;
struct max98090_priv {unsigned int dai_fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  formats; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
 unsigned int SND_SOC_DAIFMT_RIGHT_J ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max98090_dai_startup(struct snd_pcm_substream *substream,
				struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);
	unsigned int fmt = max98090->dai_fmt;

	/* Remove 24-bit format support if it is not in right justified mode. */
	if ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) != SND_SOC_DAIFMT_RIGHT_J) {
		substream->runtime->hw.formats = SNDRV_PCM_FMTBIT_S16_LE;
		snd_pcm_hw_constraint_msbits(substream->runtime, 0, 16, 16);
	}
	return 0;
}