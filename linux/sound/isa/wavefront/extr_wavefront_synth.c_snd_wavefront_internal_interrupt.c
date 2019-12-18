#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int irq_ok; int /*<<< orphan*/  interrupt_sleeper; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq_cnt; } ;
typedef  TYPE_1__ snd_wavefront_t ;
struct TYPE_6__ {TYPE_1__ wavefront; } ;
typedef  TYPE_2__ snd_wavefront_card_t ;

/* Variables and functions */
 int STAT_INTR_READ ; 
 int STAT_INTR_WRITE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int wavefront_status (TYPE_1__*) ; 

void
snd_wavefront_internal_interrupt (snd_wavefront_card_t *card)
{
	snd_wavefront_t *dev = &card->wavefront;

	/*
	   Some comments on interrupts. I attempted a version of this
	   driver that used interrupts throughout the code instead of
	   doing busy and/or sleep-waiting. Alas, it appears that once
	   the Motorola firmware is downloaded, the card *never*
	   generates an RX interrupt. These are successfully generated
	   during firmware loading, and after that wavefront_status()
	   reports that an interrupt is pending on the card from time
	   to time, but it never seems to be delivered to this
	   driver. Note also that wavefront_status() continues to
	   report that RX interrupts are enabled, suggesting that I
	   didn't goof up and disable them by mistake.

	   Thus, I stepped back to a prior version of
	   wavefront_wait(), the only place where this really
	   matters. Its sad, but I've looked through the code to check
	   on things, and I really feel certain that the Motorola
	   firmware prevents RX-ready interrupts.
	*/

	if ((wavefront_status(dev) & (STAT_INTR_READ|STAT_INTR_WRITE)) == 0) {
		return;
	}

	spin_lock(&dev->irq_lock);
	dev->irq_ok = 1;
	dev->irq_cnt++;
	spin_unlock(&dev->irq_lock);
	wake_up(&dev->interrupt_sleeper);
}