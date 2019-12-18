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
struct snd_wss {int hardware; int mode; int /*<<< orphan*/  reg_lock; scalar_t__ capture_substream; scalar_t__ playback_substream; scalar_t__ single_dma; TYPE_1__* timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  sticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231P (int /*<<< orphan*/ ) ; 
 unsigned char CS4231_ALL_IRQS ; 
 int /*<<< orphan*/  CS4231_IRQ_STATUS ; 
 unsigned char CS4231_PLAYBACK_IRQ ; 
 unsigned char CS4231_RECORD_IRQ ; 
 unsigned char CS4231_TIMER_IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  STATUS ; 
 int WSS_HW_AD1848_MASK ; 
 int WSS_HW_INTERWAVE ; 
 int WSS_MODE_PLAY ; 
 int WSS_MODE_RECORD ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  snd_timer_interrupt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned char snd_wss_in (struct snd_wss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_wss_out (struct snd_wss*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  snd_wss_overrange (struct snd_wss*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wss_outb (struct snd_wss*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

irqreturn_t snd_wss_interrupt(int irq, void *dev_id)
{
	struct snd_wss *chip = dev_id;
	unsigned char status;

	if (chip->hardware & WSS_HW_AD1848_MASK)
		/* pretend it was the only possible irq for AD1848 */
		status = CS4231_PLAYBACK_IRQ;
	else
		status = snd_wss_in(chip, CS4231_IRQ_STATUS);
	if (status & CS4231_TIMER_IRQ) {
		if (chip->timer)
			snd_timer_interrupt(chip->timer, chip->timer->sticks);
	}
	if (chip->single_dma && chip->hardware != WSS_HW_INTERWAVE) {
		if (status & CS4231_PLAYBACK_IRQ) {
			if (chip->mode & WSS_MODE_PLAY) {
				if (chip->playback_substream)
					snd_pcm_period_elapsed(chip->playback_substream);
			}
			if (chip->mode & WSS_MODE_RECORD) {
				if (chip->capture_substream) {
					snd_wss_overrange(chip);
					snd_pcm_period_elapsed(chip->capture_substream);
				}
			}
		}
	} else {
		if (status & CS4231_PLAYBACK_IRQ) {
			if (chip->playback_substream)
				snd_pcm_period_elapsed(chip->playback_substream);
		}
		if (status & CS4231_RECORD_IRQ) {
			if (chip->capture_substream) {
				snd_wss_overrange(chip);
				snd_pcm_period_elapsed(chip->capture_substream);
			}
		}
	}

	spin_lock(&chip->reg_lock);
	status = ~CS4231_ALL_IRQS | ~status;
	if (chip->hardware & WSS_HW_AD1848_MASK)
		wss_outb(chip, CS4231P(STATUS), 0);
	else
		snd_wss_out(chip, CS4231_IRQ_STATUS, status);
	spin_unlock(&chip->reg_lock);
	return IRQ_HANDLED;
}