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
struct snd_wss {int hardware; int* image; int /*<<< orphan*/  mce_mutex; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  single_dma; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 size_t AD1845_LWR_FREQ_SEL ; 
 size_t AD1845_UPR_FREQ_SEL ; 
 size_t CS4231_ALT_FEATURE_1 ; 
 size_t CS4231_IFACE_CTRL ; 
 size_t CS4231_PLAYBK_FORMAT ; 
 int CS4231_RECORD_ENABLE ; 
 size_t CS4231_REC_FORMAT ; 
 int WSS_HW_AD1845 ; 
 int WSS_HW_CS4231A ; 
 int WSS_HW_CS4232_MASK ; 
 scalar_t__ WSS_HW_INTERWAVE ; 
 scalar_t__ WSS_HW_OPL3SA2 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_wss_mce_down (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_mce_up (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_wss_playback_format(struct snd_wss *chip,
				       struct snd_pcm_hw_params *params,
				       unsigned char pdfr)
{
	unsigned long flags;
	int full_calib = 1;

	mutex_lock(&chip->mce_mutex);
	if (chip->hardware == WSS_HW_CS4231A ||
	    (chip->hardware & WSS_HW_CS4232_MASK)) {
		spin_lock_irqsave(&chip->reg_lock, flags);
		if ((chip->image[CS4231_PLAYBK_FORMAT] & 0x0f) == (pdfr & 0x0f)) {	/* rate is same? */
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				    chip->image[CS4231_ALT_FEATURE_1] | 0x10);
			chip->image[CS4231_PLAYBK_FORMAT] = pdfr;
			snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
				    chip->image[CS4231_PLAYBK_FORMAT]);
			snd_wss_out(chip, CS4231_ALT_FEATURE_1,
				    chip->image[CS4231_ALT_FEATURE_1] &= ~0x10);
			udelay(100); /* Fixes audible clicks at least on GUS MAX */
			full_calib = 0;
		}
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	} else if (chip->hardware == WSS_HW_AD1845) {
		unsigned rate = params_rate(params);

		/*
		 * Program the AD1845 correctly for the playback stream.
		 * Note that we do NOT need to toggle the MCE bit because
		 * the PLAYBACK_ENABLE bit of the Interface Configuration
		 * register is set.
		 *
		 * NOTE: We seem to need to write to the MSB before the LSB
		 *       to get the correct sample frequency.
		 */
		spin_lock_irqsave(&chip->reg_lock, flags);
		snd_wss_out(chip, CS4231_PLAYBK_FORMAT, (pdfr & 0xf0));
		snd_wss_out(chip, AD1845_UPR_FREQ_SEL, (rate >> 8) & 0xff);
		snd_wss_out(chip, AD1845_LWR_FREQ_SEL, rate & 0xff);
		full_calib = 0;
		spin_unlock_irqrestore(&chip->reg_lock, flags);
	}
	if (full_calib) {
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		if (chip->hardware != WSS_HW_INTERWAVE && !chip->single_dma) {
			if (chip->image[CS4231_IFACE_CTRL] & CS4231_RECORD_ENABLE)
				pdfr = (pdfr & 0xf0) |
				       (chip->image[CS4231_REC_FORMAT] & 0x0f);
		} else {
			chip->image[CS4231_PLAYBK_FORMAT] = pdfr;
		}
		snd_wss_out(chip, CS4231_PLAYBK_FORMAT, pdfr);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		if (chip->hardware == WSS_HW_OPL3SA2)
			udelay(100);	/* this seems to help */
		snd_wss_mce_down(chip);
	}
	mutex_unlock(&chip->mce_mutex);
}