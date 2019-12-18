#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_3__* card; struct snd_soc_dai* cpu_dai; struct snd_soc_dai* codec_dai; } ;
struct snd_soc_dai {TYPE_2__* driver; } ;
struct snd_compr_stream {int /*<<< orphan*/  direction; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  pcm_mutex; int /*<<< orphan*/  pcm_subclass; } ;
struct TYPE_5__ {TYPE_1__* cops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* trigger ) (struct snd_compr_stream*,int,struct snd_soc_dai*) ;} ;

/* Variables and functions */
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dai_digital_mute (struct snd_soc_dai*,int,int /*<<< orphan*/ ) ; 
 int soc_compr_components_trigger (struct snd_compr_stream*,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_compr_stream*,int,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_compr_trigger(struct snd_compr_stream *cstream, int cmd)
{
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	int ret;

	mutex_lock_nested(&rtd->card->pcm_mutex, rtd->card->pcm_subclass);

	ret = soc_compr_components_trigger(cstream, cmd);
	if (ret < 0)
		goto out;

	if (cpu_dai->driver->cops && cpu_dai->driver->cops->trigger)
		cpu_dai->driver->cops->trigger(cstream, cmd, cpu_dai);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_soc_dai_digital_mute(codec_dai, 0, cstream->direction);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		snd_soc_dai_digital_mute(codec_dai, 1, cstream->direction);
		break;
	}

out:
	mutex_unlock(&rtd->card->pcm_mutex);
	return ret;
}