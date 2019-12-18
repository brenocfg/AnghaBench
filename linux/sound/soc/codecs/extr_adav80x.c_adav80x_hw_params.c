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
struct snd_pcm_substream {scalar_t__ stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct adav80x {unsigned int sysclk; unsigned int rate; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  adav80x_set_adc_clock (struct snd_soc_component*,unsigned int) ; 
 int /*<<< orphan*/  adav80x_set_capture_pcm_format (struct snd_soc_component*,struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  adav80x_set_dac_clock (struct snd_soc_component*,unsigned int) ; 
 int /*<<< orphan*/  adav80x_set_deemph (struct snd_soc_component*) ; 
 int /*<<< orphan*/  adav80x_set_playback_pcm_format (struct snd_soc_component*,struct snd_soc_dai*,struct snd_pcm_hw_params*) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 struct adav80x* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adav80x_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct adav80x *adav80x = snd_soc_component_get_drvdata(component);
	unsigned int rate = params_rate(params);

	if (rate * 256 != adav80x->sysclk)
		return -EINVAL;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		adav80x_set_playback_pcm_format(component, dai, params);
		adav80x_set_dac_clock(component, rate);
	} else {
		adav80x_set_capture_pcm_format(component, dai, params);
		adav80x_set_adc_clock(component, rate);
	}
	adav80x->rate = rate;
	adav80x_set_deemph(component);

	return 0;
}