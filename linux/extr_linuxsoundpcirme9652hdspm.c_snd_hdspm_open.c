#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;
struct hdspm {int io_type; int /*<<< orphan*/  lock; struct snd_pcm_substream* capture_substream; int /*<<< orphan*/  capture_pid; struct snd_pcm_substream* playback_substream; int /*<<< orphan*/  playback_pid; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int AES32 ; 
#define  AIO 129 
#define  RayDAT 128 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_KNOT ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  hdspm_hw_constraints_aes32_sample_rates ; 
 int /*<<< orphan*/  hdspm_stop_audio (struct hdspm*) ; 
 TYPE_1__ snd_hdspm_capture_subinfo ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_in_channels ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_in_channels_rate ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_out_channels ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_out_channels_rate ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_rate_in_channels ; 
 int /*<<< orphan*/  snd_hdspm_hw_rule_rate_out_channels ; 
 TYPE_1__ snd_hdspm_playback_subinfo ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_pow2 (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_single (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct hdspm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct hdspm* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdspm_open(struct snd_pcm_substream *substream)
{
	struct hdspm *hdspm = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	bool playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	spin_lock_irq(&hdspm->lock);
	snd_pcm_set_sync(substream);
	runtime->hw = (playback) ? snd_hdspm_playback_subinfo :
		snd_hdspm_capture_subinfo;

	if (playback) {
		if (!hdspm->capture_substream)
			hdspm_stop_audio(hdspm);

		hdspm->playback_pid = current->pid;
		hdspm->playback_substream = substream;
	} else {
		if (!hdspm->playback_substream)
			hdspm_stop_audio(hdspm);

		hdspm->capture_pid = current->pid;
		hdspm->capture_substream = substream;
	}

	spin_unlock_irq(&hdspm->lock);

	snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	snd_pcm_hw_constraint_pow2(runtime, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE);

	switch (hdspm->io_type) {
	case AIO:
	case RayDAT:
		snd_pcm_hw_constraint_minmax(runtime,
					     SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					     32, 4096);
		/* RayDAT & AIO have a fixed buffer of 16384 samples per channel */
		snd_pcm_hw_constraint_single(runtime,
					     SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					     16384);
		break;

	default:
		snd_pcm_hw_constraint_minmax(runtime,
					     SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
					     64, 8192);
		snd_pcm_hw_constraint_single(runtime,
					     SNDRV_PCM_HW_PARAM_PERIODS, 2);
		break;
	}

	if (AES32 == hdspm->io_type) {
		runtime->hw.rates |= SNDRV_PCM_RATE_KNOT;
		snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				&hdspm_hw_constraints_aes32_sample_rates);
	} else {
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				(playback ?
				 snd_hdspm_hw_rule_rate_out_channels :
				 snd_hdspm_hw_rule_rate_in_channels), hdspm,
				SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	}

	snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			(playback ? snd_hdspm_hw_rule_out_channels :
			 snd_hdspm_hw_rule_in_channels), hdspm,
			SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			(playback ? snd_hdspm_hw_rule_out_channels_rate :
			 snd_hdspm_hw_rule_in_channels_rate), hdspm,
			SNDRV_PCM_HW_PARAM_RATE, -1);

	return 0;
}