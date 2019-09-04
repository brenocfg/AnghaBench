#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_sb {int open; int hardware; int dma16; int dma8; struct snd_pcm_substream* capture_substream; struct snd_pcm_substream* playback_substream; int /*<<< orphan*/  open_lock; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct TYPE_3__ {int rate_min; int rate_max; int channels_max; int buffer_bytes_max; int period_bytes_max; int /*<<< orphan*/  rates; int /*<<< orphan*/  formats; } ;
struct snd_pcm_runtime {TYPE_1__ hw; } ;

/* Variables and functions */
 int EAGAIN ; 
#define  SB_HW_201 130 
#define  SB_HW_JAZZ16 129 
#define  SB_HW_PRO 128 
 int SB_OPEN_PCM ; 
 int /*<<< orphan*/  SNDRV_PCM_FMTBIT_S16_LE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  SNDRV_PCM_RATE_8000_48000 ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  hw_constraints_clock ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_ratnums (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,...) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 TYPE_1__ snd_sb8_capture ; 
 int /*<<< orphan*/  snd_sb8_hw_constraint_channels_rate ; 
 int /*<<< orphan*/  snd_sb8_hw_constraint_rate_channels ; 
 TYPE_1__ snd_sb8_playback ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8_open(struct snd_pcm_substream *substream)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long flags;

	spin_lock_irqsave(&chip->open_lock, flags);
	if (chip->open) {
		spin_unlock_irqrestore(&chip->open_lock, flags);
		return -EAGAIN;
	}
	chip->open |= SB_OPEN_PCM;
	spin_unlock_irqrestore(&chip->open_lock, flags);
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		chip->playback_substream = substream;
		runtime->hw = snd_sb8_playback;
	} else {
		chip->capture_substream = substream;
		runtime->hw = snd_sb8_capture;
	}
	switch (chip->hardware) {
	case SB_HW_JAZZ16:
		if (chip->dma16 == 5 || chip->dma16 == 7)
			runtime->hw.formats |= SNDRV_PCM_FMTBIT_S16_LE;
		runtime->hw.rates |= SNDRV_PCM_RATE_8000_48000;
		runtime->hw.rate_min = 4000;
		runtime->hw.rate_max = 50000;
		runtime->hw.channels_max = 2;
		break;
	case SB_HW_PRO:
		runtime->hw.rate_max = 44100;
		runtime->hw.channels_max = 2;
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				    snd_sb8_hw_constraint_rate_channels, NULL,
				    SNDRV_PCM_HW_PARAM_CHANNELS,
				    SNDRV_PCM_HW_PARAM_RATE, -1);
		snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				     snd_sb8_hw_constraint_channels_rate, NULL,
				     SNDRV_PCM_HW_PARAM_RATE, -1);
		break;
	case SB_HW_201:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			runtime->hw.rate_max = 44100;
		} else {
			runtime->hw.rate_max = 15000;
		}
	default:
		break;
	}
	snd_pcm_hw_constraint_ratnums(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_constraints_clock);
	if (chip->dma8 > 3 || chip->dma16 >= 0) {
		snd_pcm_hw_constraint_step(runtime, 0,
					   SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 2);
		snd_pcm_hw_constraint_step(runtime, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 2);
		runtime->hw.buffer_bytes_max = 128 * 1024 * 1024;
		runtime->hw.period_bytes_max = 128 * 1024 * 1024;
	}
	return 0;	
}