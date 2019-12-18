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
struct uda1380_priv {int /*<<< orphan*/  work; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int R14_SILENCE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 131 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 130 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  UDA1380_MIXER ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct uda1380_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int uda1380_read_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uda1380_write_reg_cache (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uda1380_trigger(struct snd_pcm_substream *substream, int cmd,
		struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct uda1380_priv *uda1380 = snd_soc_component_get_drvdata(component);
	int mixer = uda1380_read_reg_cache(component, UDA1380_MIXER);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		uda1380_write_reg_cache(component, UDA1380_MIXER,
					mixer & ~R14_SILENCE);
		schedule_work(&uda1380->work);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		uda1380_write_reg_cache(component, UDA1380_MIXER,
					mixer | R14_SILENCE);
		schedule_work(&uda1380->work);
		break;
	}
	return 0;
}