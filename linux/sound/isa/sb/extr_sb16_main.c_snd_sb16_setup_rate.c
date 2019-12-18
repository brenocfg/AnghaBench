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
struct snd_sb {int mode; unsigned short locked_rate; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned short SB_DSP_SAMPLE_RATE_IN ; 
 unsigned short SB_DSP_SAMPLE_RATE_OUT ; 
 int SB_MODE_CAPTURE_16 ; 
 int SB_MODE_PLAYBACK_16 ; 
 int SB_RATE_LOCK ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  snd_sb_ack_16bit (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sb_ack_8bit (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_sb16_setup_rate(struct snd_sb *chip,
				unsigned short rate,
				int channel)
{
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	if (chip->mode & (channel == SNDRV_PCM_STREAM_PLAYBACK ? SB_MODE_PLAYBACK_16 : SB_MODE_CAPTURE_16))
		snd_sb_ack_16bit(chip);
	else
		snd_sb_ack_8bit(chip);
	if (!(chip->mode & SB_RATE_LOCK)) {
		chip->locked_rate = rate;
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_IN);
		snd_sbdsp_command(chip, rate >> 8);
		snd_sbdsp_command(chip, rate & 0xff);
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_OUT);
		snd_sbdsp_command(chip, rate >> 8);
		snd_sbdsp_command(chip, rate & 0xff);
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
}