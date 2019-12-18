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
struct snd_sb {int mode; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  capture_substream; int /*<<< orphan*/  playback_substream; TYPE_1__* rmidi; int /*<<< orphan*/  (* rmidi_callback ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  mixer_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SB_DSP4_IRQSTATUS ; 
 int /*<<< orphan*/  SB_DSP_DMA16_OFF ; 
 int /*<<< orphan*/  SB_DSP_DMA8_OFF ; 
 unsigned char SB_IRQTYPE_16BIT ; 
 unsigned char SB_IRQTYPE_8BIT ; 
 unsigned char SB_IRQTYPE_MPUIN ; 
 int SB_MODE_CAPTURE_16 ; 
 int SB_MODE_CAPTURE_8 ; 
 int SB_MODE_PLAYBACK_16 ; 
 int SB_MODE_PLAYBACK_8 ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sb16_csp_update (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sb_ack_16bit (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sb_ack_8bit (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int /*<<< orphan*/ ) ; 
 unsigned char snd_sbmixer_read (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

irqreturn_t snd_sb16dsp_interrupt(int irq, void *dev_id)
{
	struct snd_sb *chip = dev_id;
	unsigned char status;
	int ok;

	spin_lock(&chip->mixer_lock);
	status = snd_sbmixer_read(chip, SB_DSP4_IRQSTATUS);
	spin_unlock(&chip->mixer_lock);
	if ((status & SB_IRQTYPE_MPUIN) && chip->rmidi_callback)
		chip->rmidi_callback(irq, chip->rmidi->private_data);
	if (status & SB_IRQTYPE_8BIT) {
		ok = 0;
		if (chip->mode & SB_MODE_PLAYBACK_8) {
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_sb16_csp_update(chip);
			ok++;
		}
		if (chip->mode & SB_MODE_CAPTURE_8) {
			snd_pcm_period_elapsed(chip->capture_substream);
			ok++;
		}
		spin_lock(&chip->reg_lock);
		if (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		snd_sb_ack_8bit(chip);
		spin_unlock(&chip->reg_lock);
	}
	if (status & SB_IRQTYPE_16BIT) {
		ok = 0;
		if (chip->mode & SB_MODE_PLAYBACK_16) {
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_sb16_csp_update(chip);
			ok++;
		}
		if (chip->mode & SB_MODE_CAPTURE_16) {
			snd_pcm_period_elapsed(chip->capture_substream);
			ok++;
		}
		spin_lock(&chip->reg_lock);
		if (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
		snd_sb_ack_16bit(chip);
		spin_unlock(&chip->reg_lock);
	}
	return IRQ_HANDLED;
}