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

/* Variables and functions */
 int /*<<< orphan*/  EC_CODEC_SAMPLE_DEPTH_16 ; 
 int /*<<< orphan*/  EC_CODEC_SAMPLE_DEPTH_24 ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 129 
#define  SNDRV_PCM_FORMAT_S24_LE 128 
 int params_format (struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int set_i2s_bclk (struct snd_soc_component*,unsigned int) ; 
 int set_i2s_sample_depth (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 unsigned int snd_soc_params_to_bclk (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int cros_ec_i2s_hw_params(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *params,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	unsigned int rate, bclk;
	int ret;

	rate = params_rate(params);
	if (rate != 48000)
		return -EINVAL;

	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		ret = set_i2s_sample_depth(component, EC_CODEC_SAMPLE_DEPTH_16);
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		ret = set_i2s_sample_depth(component, EC_CODEC_SAMPLE_DEPTH_24);
		break;
	default:
		return -EINVAL;
	}
	if (ret < 0)
		return ret;

	bclk = snd_soc_params_to_bclk(params);
	return set_i2s_bclk(component, bclk);
}