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
struct snd_cs4231 {unsigned int mode; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231U (struct snd_cs4231*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4231_IRQ_STATUS ; 
 int CS4231_MODE_OPEN ; 
 int CS4231_PLAYBACK_IRQ ; 
 int CS4231_RECORD_IRQ ; 
 int CS4231_TIMER_IRQ ; 
 int EAGAIN ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  __cs4231_writeb (struct snd_cs4231*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_cs4231_out (struct snd_cs4231*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_cs4231_open(struct snd_cs4231 *chip, unsigned int mode)
{
	unsigned long flags;

	mutex_lock(&chip->open_mutex);
	if ((chip->mode & mode)) {
		mutex_unlock(&chip->open_mutex);
		return -EAGAIN;
	}
	if (chip->mode & CS4231_MODE_OPEN) {
		chip->mode |= mode;
		mutex_unlock(&chip->open_mutex);
		return 0;
	}
	/* ok. now enable and ack CODEC IRQ */
	spin_lock_irqsave(&chip->lock, flags);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, CS4231_PLAYBACK_IRQ |
		       CS4231_RECORD_IRQ |
		       CS4231_TIMER_IRQ);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */
	__cs4231_writeb(chip, 0, CS4231U(chip, STATUS));	/* clear IRQ */

	snd_cs4231_out(chip, CS4231_IRQ_STATUS, CS4231_PLAYBACK_IRQ |
		       CS4231_RECORD_IRQ |
		       CS4231_TIMER_IRQ);
	snd_cs4231_out(chip, CS4231_IRQ_STATUS, 0);

	spin_unlock_irqrestore(&chip->lock, flags);

	chip->mode = mode;
	mutex_unlock(&chip->open_mutex);
	return 0;
}