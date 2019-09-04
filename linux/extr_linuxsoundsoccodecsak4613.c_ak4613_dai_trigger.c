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
struct ak4613_priv {int /*<<< orphan*/  dummy_write_work; struct snd_soc_component* component; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int SNDRV_PCM_TRIGGER_RESUME ; 
 int SNDRV_PCM_TRIGGER_START ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct ak4613_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4613_dai_trigger(struct snd_pcm_substream *substream, int cmd,
			      struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ak4613_priv *priv = snd_soc_component_get_drvdata(component);

	/*
	 * FIXME
	 *
	 * PW_MGMT1 / PW_MGMT3 needs dummy write at least after 5 LR clocks
	 * from Power Down Release. Otherwise, Playback volume will be 0dB.
	 * To avoid complex multiple delay/dummy_write method from
	 * ak4613_set_bias_level() / SND_SOC_DAPM_DAC_E("DACx", ...),
	 * call it once here.
	 *
	 * But, unfortunately, we can't "write" here because here is atomic
	 * context (It uses I2C access for writing).
	 * Thus, use schedule_work() to switching to normal context
	 * immediately.
	 *
	 * Note
	 *
	 * Calling ak4613_dummy_write() function might be delayed.
	 * In such case, ak4613 volume might be temporarily 0dB when
	 * beggining of playback.
	 * see also
	 *	ak4613_dummy_write()
	 */

	if ((cmd != SNDRV_PCM_TRIGGER_START) &&
	    (cmd != SNDRV_PCM_TRIGGER_RESUME))
		return 0;

	if (substream->stream != SNDRV_PCM_STREAM_PLAYBACK)
		return  0;

	priv->component = component;
	schedule_work(&priv->dummy_write_work);

	return 0;
}