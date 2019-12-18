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
struct snd_wss {unsigned int mode; int hardware; int* image; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_IRQ_ENABLE ; 
 size_t CS4231_IRQ_STATUS ; 
 size_t CS4231_PIN_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 int CS4231_PLAYBACK_PIO ; 
 int CS4231_RECORD_ENABLE ; 
 int CS4231_RECORD_PIO ; 
 int /*<<< orphan*/  STATUS ; 
 int WSS_HW_AD1848_MASK ; 
 int WSS_MODE_OPEN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_wss_mce_down (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_mce_up (struct snd_wss*) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_wss_close(struct snd_wss *chip, unsigned int mode)
{
	unsigned long flags;

	mutex_lock(&chip->open_mutex);
	chip->mode &= ~mode;
	if (chip->mode & WSS_MODE_OPEN) {
		mutex_unlock(&chip->open_mutex);
		return;
	}
	/* disable IRQ */
	spin_lock_irqsave(&chip->reg_lock, flags);
	if (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	chip->image[CS4231_PIN_CTRL] &= ~CS4231_IRQ_ENABLE;
	snd_wss_out(chip, CS4231_PIN_CTRL, chip->image[CS4231_PIN_CTRL]);

	/* now disable record & playback */

	if (chip->image[CS4231_IFACE_CTRL] & (CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
					       CS4231_RECORD_ENABLE | CS4231_RECORD_PIO)) {
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_up(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
		chip->image[CS4231_IFACE_CTRL] &= ~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
						     CS4231_RECORD_ENABLE | CS4231_RECORD_PIO);
		snd_wss_out(chip, CS4231_IFACE_CTRL,
			    chip->image[CS4231_IFACE_CTRL]);
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		snd_wss_mce_down(chip);
		spin_lock_irqsave(&chip->reg_lock, flags);
	}

	/* clear IRQ again */
	if (!(chip->hardware & WSS_HW_AD1848_MASK))
		snd_wss_out(chip, CS4231_IRQ_STATUS, 0);
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	wss_outb(chip, CS4231P(STATUS), 0);	/* clear IRQ */
	spin_unlock_irqrestore(&chip->reg_lock, flags);

	chip->mode = 0;
	mutex_unlock(&chip->open_mutex);
}