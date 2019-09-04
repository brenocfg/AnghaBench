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
struct voicehat_priv {scalar_t__ sdmode_delay_jiffies; int /*<<< orphan*/  sdmode_gpio; int /*<<< orphan*/  enable_sdmode_work; } ;
struct snd_soc_dai {int playback_active; int capture_active; int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct voicehat_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int voicehat_daiops_trigger(struct snd_pcm_substream *substream, int cmd,
				   struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct voicehat_priv *voicehat =
				snd_soc_component_get_drvdata(component);

	if (voicehat->sdmode_delay_jiffies == 0)
		return 0;

	dev_dbg(dai->dev, "CMD             %d", cmd);
	dev_dbg(dai->dev, "Playback Active %d", dai->playback_active);
	dev_dbg(dai->dev, "Capture Active  %d", dai->capture_active);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (dai->playback_active) {
			dev_info(dai->dev, "Enabling audio amp...\n");
			queue_delayed_work(
				system_power_efficient_wq,
				&voicehat->enable_sdmode_work,
				voicehat->sdmode_delay_jiffies);
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (dai->playback_active) {
			cancel_delayed_work(&voicehat->enable_sdmode_work);
			dev_info(dai->dev, "Disabling audio amp...\n");
			gpiod_set_value(voicehat->sdmode_gpio, 0);
		}
		break;
	}
	return 0;
}