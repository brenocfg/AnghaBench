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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct pcm3168a_priv {TYPE_1__* io_params; } ;
struct TYPE_2__ {int fmt; int tdm_slots; } ;

/* Variables and functions */
#define  PCM3168A_FMT_DSP_A 132 
#define  PCM3168A_FMT_DSP_B 131 
#define  PCM3168A_FMT_I2S 130 
#define  PCM3168A_FMT_LEFT_J 129 
#define  PCM3168A_FMT_RIGHT_J 128 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_SAMPLE_BITS ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 struct pcm3168a_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3168a_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	unsigned int sample_min;
	unsigned int channel_max;
	unsigned int channel_maxs[] = {
		8, /* DAC */
		6  /* ADC */
	};

	/*
	 * Available Data Bits
	 *
	 * RIGHT_J : 24 / 16
	 * LEFT_J  : 24
	 * I2S     : 24
	 *
	 * TDM available
	 *
	 * I2S
	 * LEFT_J
	 */
	switch (pcm3168a->io_params[dai->id].fmt) {
	case PCM3168A_FMT_RIGHT_J:
		sample_min  = 16;
		channel_max =  2;
		break;
	case PCM3168A_FMT_LEFT_J:
	case PCM3168A_FMT_I2S:
	case PCM3168A_FMT_DSP_A:
	case PCM3168A_FMT_DSP_B:
		sample_min  = 24;
		channel_max = channel_maxs[dai->id];
		break;
	default:
		sample_min  = 24;
		channel_max =  2;
	}

	snd_pcm_hw_constraint_minmax(substream->runtime,
				     SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
				     sample_min, 32);

	/* Allow all channels in multi DIN/DOUT mode */
	if (pcm3168a->io_params[dai->id].tdm_slots == 2)
		channel_max = channel_maxs[dai->id];

	snd_pcm_hw_constraint_minmax(substream->runtime,
				     SNDRV_PCM_HW_PARAM_CHANNELS,
				     2, channel_max);

	return 0;
}