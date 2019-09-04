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
struct snd_sb {int mode; int /*<<< orphan*/  reg_lock; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SB_DSP_DMA16_OFF ; 
 int /*<<< orphan*/  SB_DSP_DMA16_ON ; 
 int /*<<< orphan*/  SB_DSP_DMA8_OFF ; 
 int /*<<< orphan*/  SB_DSP_DMA8_ON ; 
 int SB_MODE_CAPTURE_16 ; 
 int SB_MODE_PLAYBACK_16 ; 
 int SB_RATE_LOCK_CAPTURE ; 
 int SB_RATE_LOCK_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sb16_playback_trigger(struct snd_pcm_substream *substream,
				     int cmd)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	int result = 0;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_PLAYBACK;
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PLAYBACK_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PLAYBACK_16 ? SB_DSP_DMA16_OFF : SB_DSP_DMA8_OFF);
		/* next two lines are needed for some types of DSP4 (SB AWE 32 - 4.13) */
		if (chip->mode & SB_RATE_LOCK_CAPTURE)
			snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTURE_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		chip->mode &= ~SB_RATE_LOCK_PLAYBACK;
		break;
	default:
		result = -EINVAL;
	}
	spin_unlock(&chip->reg_lock);
	return result;
}