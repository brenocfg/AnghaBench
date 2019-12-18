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
struct aic23 {scalar_t__ requested_adc; scalar_t__ requested_dac; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  TLV320AIC23_ACTIVE ; 
 struct aic23* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_is_active (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tlv320aic23_shutdown(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct aic23 *aic23 = snd_soc_component_get_drvdata(component);

	/* deactivate */
	if (!snd_soc_component_is_active(component)) {
		udelay(50);
		snd_soc_component_write(component, TLV320AIC23_ACTIVE, 0x0);
	}
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aic23->requested_dac = 0;
	else
		aic23->requested_adc = 0;
}