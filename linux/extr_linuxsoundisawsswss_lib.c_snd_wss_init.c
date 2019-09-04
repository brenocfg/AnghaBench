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
struct snd_wss {int* image; int hardware; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 size_t CS4231_ALT_FEATURE_1 ; 
 size_t CS4231_ALT_FEATURE_2 ; 
 int CS4231_AUTOCALIB ; 
 int CS4231_CALIB_MODE ; 
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 int CS4231_PLAYBACK_PIO ; 
 size_t CS4231_PLAYBK_FORMAT ; 
 int CS4231_RECORD_ENABLE ; 
 int CS4231_RECORD_PIO ; 
 size_t CS4231_REC_FORMAT ; 
 int WSS_HW_AD1848_MASK ; 
 int /*<<< orphan*/  snd_wss_calibrate_mute (struct snd_wss*,int) ; 
 int /*<<< orphan*/  snd_wss_mce_down (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_mce_up (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_wss_init(struct snd_wss *chip)
{
	unsigned long flags;

	snd_wss_calibrate_mute(chip, 1);
	snd_wss_mce_down(chip);

#ifdef SNDRV_DEBUG_MCE
	snd_printk(KERN_DEBUG "init: (1)\n");
#endif
	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE |
					    CS4231_PLAYBACK_PIO |
					    CS4231_RECORD_ENABLE |
					    CS4231_RECORD_PIO |
					    CS4231_CALIB_MODE);
	chip->image[CS4231_IFACE_CTRL] |= CS4231_AUTOCALIB;
	snd_wss_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_down(chip);

#ifdef SNDRV_DEBUG_MCE
	snd_printk(KERN_DEBUG "init: (2)\n");
#endif

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	chip->image[CS4231_IFACE_CTRL] &= ~CS4231_AUTOCALIB;
	snd_wss_out(chip, CS4231_IFACE_CTRL, chip->image[CS4231_IFACE_CTRL]);
	snd_wss_out(chip,
		    CS4231_ALT_FEATURE_1, chip->image[CS4231_ALT_FEATURE_1]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_down(chip);

#ifdef SNDRV_DEBUG_MCE
	snd_printk(KERN_DEBUG "init: (3) - afei = 0x%x\n",
		   chip->image[CS4231_ALT_FEATURE_1]);
#endif

	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_wss_out(chip, CS4231_ALT_FEATURE_2,
		    chip->image[CS4231_ALT_FEATURE_2]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_wss_out(chip, CS4231_PLAYBK_FORMAT,
		    chip->image[CS4231_PLAYBK_FORMAT]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_down(chip);

#ifdef SNDRV_DEBUG_MCE
	snd_printk(KERN_DEBUG "init: (4)\n");
#endif

	snd_wss_mce_up(chip);
	spin_lock_irqsave(&chip->reg_lock, flags);
	if (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_REC_FORMAT,
			    chip->image[CS4231_REC_FORMAT]);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_wss_mce_down(chip);
	snd_wss_calibrate_mute(chip, 0);

#ifdef SNDRV_DEBUG_MCE
	snd_printk(KERN_DEBUG "init: (5)\n");
#endif
}