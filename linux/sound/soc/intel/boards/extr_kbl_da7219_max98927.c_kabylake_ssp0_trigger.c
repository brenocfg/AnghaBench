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
struct snd_soc_pcm_runtime {int num_codecs; int /*<<< orphan*/  dev; struct snd_soc_dai** codec_dais; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {char* name; char* name_prefix; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  MAX98373_DEV0_NAME ; 
 int /*<<< orphan*/  MAX98373_DEV1_NAME ; 
 int /*<<< orphan*/  MAX98927_DEV0_NAME ; 
 int /*<<< orphan*/  MAX98927_DEV1_NAME ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int snd_soc_dapm_disable_pin (struct snd_soc_dapm_context*,char*) ; 
 int snd_soc_dapm_enable_pin (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kabylake_ssp0_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int j, ret;

	for (j = 0; j < rtd->num_codecs; j++) {
		struct snd_soc_dai *codec_dai = rtd->codec_dais[j];
		const char *name = codec_dai->component->name;
		struct snd_soc_component *component = codec_dai->component;
		struct snd_soc_dapm_context *dapm =
				snd_soc_component_get_dapm(component);
		char pin_name[20];

		if (strcmp(name, MAX98927_DEV0_NAME) &&
			strcmp(name, MAX98927_DEV1_NAME) &&
			strcmp(name, MAX98373_DEV0_NAME) &&
			strcmp(name, MAX98373_DEV1_NAME))
			continue;

		snprintf(pin_name, ARRAY_SIZE(pin_name), "%s Spk",
			codec_dai->component->name_prefix);

		switch (cmd) {
		case SNDRV_PCM_TRIGGER_START:
		case SNDRV_PCM_TRIGGER_RESUME:
		case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			ret = snd_soc_dapm_enable_pin(dapm, pin_name);
			if (ret) {
				dev_err(rtd->dev, "failed to enable %s: %d\n",
				pin_name, ret);
				return ret;
			}
			snd_soc_dapm_sync(dapm);
			break;
		case SNDRV_PCM_TRIGGER_STOP:
		case SNDRV_PCM_TRIGGER_SUSPEND:
		case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			ret = snd_soc_dapm_disable_pin(dapm, pin_name);
			if (ret) {
				dev_err(rtd->dev, "failed to disable %s: %d\n",
				pin_name, ret);
				return ret;
			}
			snd_soc_dapm_sync(dapm);
			break;
		}
	}

	return 0;
}