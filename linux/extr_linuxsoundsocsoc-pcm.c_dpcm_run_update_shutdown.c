#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_1__* dai_link; } ;
struct snd_pcm_substream {int dummy; } ;
typedef  enum snd_soc_dpcm_trigger { ____Placeholder_snd_soc_dpcm_trigger } snd_soc_dpcm_trigger ;
struct TYPE_2__ {int* trigger; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_TRIGGER_STOP ; 
 int /*<<< orphan*/  SND_SOC_DAPM_STREAM_NOP ; 
 int SND_SOC_DPCM_TRIGGER_BESPOKE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dpcm_be_dai_hw_free (struct snd_soc_pcm_runtime*,int) ; 
 int dpcm_be_dai_shutdown (struct snd_soc_pcm_runtime*,int) ; 
 int dpcm_be_dai_trigger (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcm_dapm_stream_event (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 
 struct snd_pcm_substream* snd_soc_dpcm_get_substream (struct snd_soc_pcm_runtime*,int) ; 
 int soc_pcm_bespoke_trigger (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpcm_run_update_shutdown(struct snd_soc_pcm_runtime *fe, int stream)
{
	struct snd_pcm_substream *substream =
		snd_soc_dpcm_get_substream(fe, stream);
	enum snd_soc_dpcm_trigger trigger = fe->dai_link->trigger[stream];
	int err;

	dev_dbg(fe->dev, "ASoC: runtime %s close on FE %s\n",
			stream ? "capture" : "playback", fe->dai_link->name);

	if (trigger == SND_SOC_DPCM_TRIGGER_BESPOKE) {
		/* call bespoke trigger - FE takes care of all BE triggers */
		dev_dbg(fe->dev, "ASoC: bespoke trigger FE %s cmd stop\n",
				fe->dai_link->name);

		err = soc_pcm_bespoke_trigger(substream, SNDRV_PCM_TRIGGER_STOP);
		if (err < 0)
			dev_err(fe->dev,"ASoC: trigger FE failed %d\n", err);
	} else {
		dev_dbg(fe->dev, "ASoC: trigger FE %s cmd stop\n",
			fe->dai_link->name);

		err = dpcm_be_dai_trigger(fe, stream, SNDRV_PCM_TRIGGER_STOP);
		if (err < 0)
			dev_err(fe->dev,"ASoC: trigger FE failed %d\n", err);
	}

	err = dpcm_be_dai_hw_free(fe, stream);
	if (err < 0)
		dev_err(fe->dev,"ASoC: hw_free FE failed %d\n", err);

	err = dpcm_be_dai_shutdown(fe, stream);
	if (err < 0)
		dev_err(fe->dev,"ASoC: shutdown FE failed %d\n", err);

	/* run the stream event for each BE */
	dpcm_dapm_stream_event(fe, stream, SND_SOC_DAPM_STREAM_NOP);

	return 0;
}