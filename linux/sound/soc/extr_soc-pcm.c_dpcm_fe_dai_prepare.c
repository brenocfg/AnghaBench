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
struct snd_soc_pcm_runtime {TYPE_3__* card; TYPE_2__* dpcm; TYPE_1__* dai_link; int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  be_clients; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SND_SOC_CARD_CLASS_RUNTIME ; 
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_START ; 
 int /*<<< orphan*/  SND_SOC_DPCM_STATE_PREPARE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_FE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_NO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dpcm_be_dai_prepare (struct snd_soc_pcm_runtime*,int) ; 
 int /*<<< orphan*/  dpcm_dapm_stream_event (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcm_set_fe_update_state (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int soc_pcm_prepare (struct snd_pcm_substream*) ; 

__attribute__((used)) static int dpcm_fe_dai_prepare(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *fe = substream->private_data;
	int stream = substream->stream, ret = 0;

	mutex_lock_nested(&fe->card->mutex, SND_SOC_CARD_CLASS_RUNTIME);

	dev_dbg(fe->dev, "ASoC: prepare FE %s\n", fe->dai_link->name);

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_FE);

	/* there is no point preparing this FE if there are no BEs */
	if (list_empty(&fe->dpcm[stream].be_clients)) {
		dev_err(fe->dev, "ASoC: no backend DAIs enabled for %s\n",
				fe->dai_link->name);
		ret = -EINVAL;
		goto out;
	}

	ret = dpcm_be_dai_prepare(fe, substream->stream);
	if (ret < 0)
		goto out;

	/* call prepare on the frontend */
	ret = soc_pcm_prepare(substream);
	if (ret < 0) {
		dev_err(fe->dev,"ASoC: prepare FE %s failed\n",
			fe->dai_link->name);
		goto out;
	}

	/* run the stream event for each BE */
	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_START);
	fe->dpcm[stream].state = SND_SOC_DPCM_STATE_PREPARE;

out:
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);
	mutex_unlock(&fe->card->mutex);

	return ret;
}