#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_2__* dpcm; TYPE_1__* dai_link; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
typedef  enum snd_soc_dpcm_trigger { ____Placeholder_snd_soc_dpcm_trigger } snd_soc_dpcm_trigger ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_update; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int* trigger; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 136 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 135 
#define  SNDRV_PCM_TRIGGER_RESUME 134 
#define  SNDRV_PCM_TRIGGER_START 133 
#define  SNDRV_PCM_TRIGGER_STOP 132 
#define  SNDRV_PCM_TRIGGER_SUSPEND 131 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_PAUSED ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_START ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_STOP ; 
#define  SND_SOC_DPCM_TRIGGER_BESPOKE 130 
#define  SND_SOC_DPCM_TRIGGER_POST 129 
#define  SND_SOC_DPCM_TRIGGER_PRE 128 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_FE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_NO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int dpcm_be_dai_trigger (struct snd_soc_pcm_runtime*,int,int) ; 
 int soc_pcm_bespoke_trigger (struct snd_pcm_substream*,int) ; 
 int soc_pcm_trigger (struct snd_pcm_substream*,int) ; 

__attribute__((used)) static int dpcm_fe_dai_do_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *fe = substream->private_data;
	int stream = substream->stream, ret;
	enum snd_soc_dpcm_trigger trigger = fe->dai_link->trigger[stream];

	fe->dpcm[stream].runtime_update = SND_SOC_DPCM_UPDATE_FE;

	switch (trigger) {
	case SND_SOC_DPCM_TRIGGER_PRE:
		/* call trigger on the frontend before the backend. */

		dev_dbg(fe->dev, "ASoC: pre trigger FE %s cmd %d\n",
				fe->dai_link->name, cmd);

		ret = soc_pcm_trigger(substream, cmd);
		if (ret < 0) {
			dev_err(fe->dev,"ASoC: trigger FE failed %d\n", ret);
			goto out;
		}

		ret = dpcm_be_dai_trigger(fe, substream->stream, cmd);
		break;
	case SND_SOC_DPCM_TRIGGER_POST:
		/* call trigger on the frontend after the backend. */

		ret = dpcm_be_dai_trigger(fe, substream->stream, cmd);
		if (ret < 0) {
			dev_err(fe->dev,"ASoC: trigger FE failed %d\n", ret);
			goto out;
		}

		dev_dbg(fe->dev, "ASoC: post trigger FE %s cmd %d\n",
				fe->dai_link->name, cmd);

		ret = soc_pcm_trigger(substream, cmd);
		break;
	case SND_SOC_DPCM_TRIGGER_BESPOKE:
		/* bespoke trigger() - handles both FE and BEs */

		dev_dbg(fe->dev, "ASoC: bespoke trigger FE %s cmd %d\n",
				fe->dai_link->name, cmd);

		ret = soc_pcm_bespoke_trigger(substream, cmd);
		if (ret < 0) {
			dev_err(fe->dev,"ASoC: trigger FE failed %d\n", ret);
			goto out;
		}
		break;
	default:
		dev_err(fe->dev, "ASoC: invalid trigger cmd %d for %s\n", cmd,
				fe->dai_link->name);
		ret = -EINVAL;
		goto out;
	}

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
	return ret;
}