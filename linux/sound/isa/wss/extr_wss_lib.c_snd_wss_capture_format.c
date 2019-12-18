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
struct snd_wss {int hardware; int* image; int /*<<< orphan*/  mce_mutex; int /*<<< orphan*/  reg_lock; scalar_t__ single_dma; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 size_t AD1845_LWR_FREQ_SEL ; 
 size_t AD1845_UPR_FREQ_SEL ; 
 size_t CS4231_ALT_FEATURE_1 ; 
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 size_t CS4231_PLAYBK_FORMAT ; 
 size_t CS4231_REC_FORMAT ; 
 int WSS_HW_AD1845 ; 
 int WSS_HW_AD1848_MASK ; 
 int WSS_HW_CS4231A ; 
 int WSS_HW_CS4232_MASK ; 
 int WSS_HW_INTERWAVE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_wss_mce_down (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_mce_up (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_wss_capture_format(struct snd_wss *chip,
				   struct snd_pcm_hw_params *params,
				   unsigned char cdfr)
{
	unsigned long flags;
	int full_calib = 1;

	mutex_lock(&chip->mce_mutex);
	if (chip->hardware == WSS_HW_CS4231A ||
	    (chip->hardware & WSS_HW_CS4232_MASK)) {
		spin_lock_irqsave(&chip->reg_lock, flags);
		if ((chip->image[CS4231_PLAYBK_FORMAT] & 0x0f) == (cdfr & 0x0f) ||	/* rate is same? */
		    (chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) {
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				chip->image[CS4231_ALT_FEATURE_1] | 0x20);
			snd_wss_out(chip, CS4231_REC_FORMAT,
				chip->image[CS4231_REC_FORMAT] = cdfr);
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				chip->image[CS4231_ALT_FEATURE_1] &= ~0x20);
			full_calib = 0;
		}
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	} else if (chip->hardware == WSS_HW_AD1845) {
		unsigned rate = params_rate(params);

		/*
		 * Program the AD1845 correctly for the capture stream.
		 * Note that we do NOT need to toggle the MCE bit because
		 * the PLAYBACK_ENABLE bit of the Interface Configuration
		 * register is set.
		 *
		 * NOTE: We seem to need to write to the MSB before the LSB
		 *       to get the correct sample frequency.
		 */
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_wss_out(chip, CS4231_REC_FORMAT, (cdfr & 0xf0));
		snd_wss_out(chip, AD1845_UPR_FREQ_SEL, (rate >> 8) & 0xff);
		snd_wss_out(chip, AD1845_LWR_FREQ_SEL, rate & 0xff);
		full_calib = 0;
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	}
	if (full_calib) {
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		if (chip->hardware != WSS_HW_INTERWAVE &&
		    !(chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE)) {
			if (chip->single_dma)
				snd_wss_out(chip, CS4231_PLAYBK_FORMAT, cdfr);
			else
				snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
				   (chip->image[CS4231_PLAYBK_FORMAT] & 0xf0) |
				   (cdfr & 0x0f));
			spin_unlock_irqrestore(&chip->reg_lock, flags);
			snd_wss_mce_down(chip);
			snd_wss_mce_up(chip);
			spin_lock_irqsave(&chip->reg_lock, flags);
		}
		if (chip->hardware & WSS_HW_AD1848_MASK)
			snd_wss_out(chip, CS4231_PLAYBK_FORMAT, cdfr);
		else
			snd_wss_out(chip, CS4231_REC_FORMAT, cdfr);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_down(chip);
	}
	mutex_unlock(&chip->mce_mutex);
}