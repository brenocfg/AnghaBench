#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_4__* card; TYPE_3__* dpcm; struct snd_soc_dai* cpu_dai; } ;
struct snd_soc_dai {TYPE_2__* driver; } ;
struct snd_compr_stream {scalar_t__ direction; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {int /*<<< orphan*/  runtime_update; int /*<<< orphan*/  state; } ;
struct TYPE_6__ {TYPE_1__* cops; } ;
struct TYPE_5__ {int (* trigger ) (struct snd_compr_stream*,int,struct snd_soc_dai*) ;} ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 scalar_t__ SND_COMPRESS_PLAYBACK ; 
 int SND_COMPR_TRIGGER_DRAIN ; 
 int SND_COMPR_TRIGGER_PARTIAL_DRAIN ; 
 int /*<<< orphan*/  SND_SOC_CARD_CLASS_RUNTIME ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_PAUSED ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_START ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_STOP ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_FE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_NO ; 
 int dpcm_be_dai_trigger (struct snd_soc_pcm_runtime*,int,int) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int soc_compr_components_trigger (struct snd_compr_stream*,int) ; 
 int stub1 (struct snd_compr_stream*,int,struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_compr_trigger_fe(struct snd_compr_stream *cstream, int cmd)
{
	struct snd_soc_pcm_runtime *fe = cstream->private_data;
	struct snd_soc_dai *cpu_dai = fe->cpu_dai;
	int ret, stream;

	if (cmd == SND_COMPR_TRIGGER_PARTIAL_DRAIN ||
	    cmd == SND_COMPR_TRIGGER_DRAIN)
		return soc_compr_components_trigger(cstream, cmd);

	if (cstream->direction == SND_COMPRESS_PLAYBACK)
		stream = SNDRV_PCM_STREAM_PLAYBACK;
	else
		stream = SNDRV_PCM_STREAM_CAPTURE;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	if (cpu_dai->driver->cops && cpu_dai->driver->cops->trigger) {
		ret = cpu_dai->driver->cops->trigger(cstream, cmd, cpu_dai);
		if (ret < 0)
			goto out;
	}

	ret = soc_compr_components_trigger(cstream, cmd);
	if (ret < 0)
		goto out;

	fe->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_FE;

	ret = dpcm_be_dai_trigger(fe, stream, cmd);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_START;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_STOP;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PAUSED;
		break;
	}

out:
	fe->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_NO;
	mutex_unlock(&fe->card->mutex);
	return ret;
}