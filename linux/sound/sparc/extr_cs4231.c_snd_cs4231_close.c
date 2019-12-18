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
struct snd_cs4231 {unsigned int mode; int* image; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 size_t CS4231_IFACE_CTRL ; 
 size_t CS4231_IRQ_STATUS ; 
 int CS4231_MODE_OPEN ; 
 int CS4231_PLAYBACK_ENABLE ; 
 int CS4231_PLAYBACK_PIO ; 
 int CS4231_RECORD_ENABLE ; 
 int CS4231_RECORD_PIO ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  __cs4231_writeb (struct snd_cs4231*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cs4231_calibrate_mute (struct snd_cs4231*,int) ; 
 int /*<<< orphan*/  snd_cs4231_mce_down (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_mce_up (struct snd_cs4231*) ; 
 int /*<<< orphan*/  snd_cs4231_out (struct snd_cs4231*,size_t,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_cs4231_close(struct snd_cs4231 *chip, unsigned int mode)
{
	unsigned long flags;

	mutex_lock(&chip->open_mutex);
	chip->mode &= ~mode;
	if (chip->mode & CS4231_MODE_OPEN) {
		mutex_unlock(&chip->open_mutex);
		return;
	}
	snd_cs4231_calibrate_mute(chip, 1);

	/* disable IRQ */
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */

	/* now disable record & playback */

	if (chip->image[CS4231_IFACE_CTRL] &
	    (CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
	     CS4231_RECORD_ENABLE | CS4231_RECORD_PIO)) {
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_up(chip);
		spin_lock_irqsave(&chip->lock, flags);
		chip->image[CS4231_IFACE_CTRL] &=
			~(CS4231_PLAYBACK_ENABLE | CS4231_PLAYBACK_PIO |
			  CS4231_RECORD_ENABLE | CS4231_RECORD_PIO);
		snd_cs4231_out(chip, CS4231_IFACE_CTRL,
				chip->image[CS4231_IFACE_CTRL]);
		spin_unlock_irqrestore(&chip->lock, flags);
		snd_cs4231_mce_down(chip);
		spin_lock_irqsave(&chip->lock, flags);
	}

	/* clear IRQ again */
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	spin_unlock_irqrestore(&chip->lock, flags);

	snd_cs4231_calibrate_mute(chip, 0);

	chip->mode = 0;
	mutex_unlock(&chip->open_mutex);
}