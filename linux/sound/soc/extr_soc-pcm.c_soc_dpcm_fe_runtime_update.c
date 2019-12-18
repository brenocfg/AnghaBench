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
struct snd_soc_pcm_runtime {TYPE_1__* dai_link; int /*<<< orphan*/  dev; TYPE_2__* codec_dai; TYPE_2__* cpu_dai; } ;
struct snd_soc_dapm_widget_list {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  capture_active; int /*<<< orphan*/  playback_active; int /*<<< orphan*/  active; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dpcm_be_disconnect (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcm_clear_pending_state (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int dpcm_path_get (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,struct snd_soc_dapm_widget_list**) ; 
 int /*<<< orphan*/  dpcm_path_put (struct snd_soc_dapm_widget_list**) ; 
 int dpcm_process_paths (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,struct snd_soc_dapm_widget_list**,int) ; 
 int /*<<< orphan*/  dpcm_run_new_update (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpcm_run_old_update (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_stream_valid (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_dpcm_fe_runtime_update(struct snd_soc_pcm_runtime *fe, int new)
{
	struct snd_soc_dapm_widget_list *list;
	int count, paths;

	if (!fe->dai_link->dynamic)
		return 0;

	/* only check active links */
	if (!fe->cpu_dai->active)
		return 0;

	/* DAPM sync will call this to update DSP paths */
	dev_dbg(fe->dev, "ASoC: DPCM %s runtime update for FE %s\n",
		new ? "new" : "old", fe->dai_link->name);

	/* skip if FE doesn't have playback capability */
	if (!snd_soc_dai_stream_valid(fe->cpu_dai,   SNDRV_PCM_STREAM_PLAYBACK) ||
	    !snd_soc_dai_stream_valid(fe->codec_dai, SNDRV_PCM_STREAM_PLAYBACK))
		goto capture;

	/* skip if FE isn't currently playing */
	if (!fe->cpu_dai->playback_active || !fe->codec_dai->playback_active)
		goto capture;

	paths = dpcm_path_get(fe, SNDRV_PCM_STREAM_PLAYBACK, &list);
	if (paths < 0) {
		dev_warn(fe->dev, "ASoC: %s no valid %s path\n",
			 fe->dai_link->name,  "playback");
		return paths;
	}

	/* update any playback paths */
	count = dpcm_process_paths(fe, SNDRV_PCM_STREAM_PLAYBACK, &list, new);
	if (count) {
		if (new)
			dpcm_run_new_update(fe, SNDRV_PCM_STREAM_PLAYBACK);
		else
			dpcm_run_old_update(fe, SNDRV_PCM_STREAM_PLAYBACK);

		dpcm_clear_pending_state(fe, SNDRV_PCM_STREAM_PLAYBACK);
		dpcm_be_disconnect(fe, SNDRV_PCM_STREAM_PLAYBACK);
	}

	dpcm_path_put(&list);

capture:
	/* skip if FE doesn't have capture capability */
	if (!snd_soc_dai_stream_valid(fe->cpu_dai,   SNDRV_PCM_STREAM_CAPTURE) ||
	    !snd_soc_dai_stream_valid(fe->codec_dai, SNDRV_PCM_STREAM_CAPTURE))
		return 0;

	/* skip if FE isn't currently capturing */
	if (!fe->cpu_dai->capture_active || !fe->codec_dai->capture_active)
		return 0;

	paths = dpcm_path_get(fe, SNDRV_PCM_STREAM_CAPTURE, &list);
	if (paths < 0) {
		dev_warn(fe->dev, "ASoC: %s no valid %s path\n",
			 fe->dai_link->name,  "capture");
		return paths;
	}

	/* update any old capture paths */
	count = dpcm_process_paths(fe, SNDRV_PCM_STREAM_CAPTURE, &list, new);
	if (count) {
		if (new)
			dpcm_run_new_update(fe, SNDRV_PCM_STREAM_CAPTURE);
		else
			dpcm_run_old_update(fe, SNDRV_PCM_STREAM_CAPTURE);

		dpcm_clear_pending_state(fe, SNDRV_PCM_STREAM_CAPTURE);
		dpcm_be_disconnect(fe, SNDRV_PCM_STREAM_CAPTURE);
	}

	dpcm_path_put(&list);

	return 0;
}