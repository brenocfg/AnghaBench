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
struct tlv320dac33_priv {scalar_t__ fifo_mode; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  t_stamp1; } ;
struct snd_soc_component {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DAC33_FIFO_MODE7 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct tlv320dac33_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t dac33_interrupt_handler(int irq, void *dev)
{
	struct snd_soc_component *component = dev;
	struct tlv320dac33_priv *dac33 = snd_soc_component_get_drvdata(component);
	unsigned long flags;

	spin_lock_irqsave(&dac33->lock, flags);
	dac33->t_stamp1 = ktime_to_us(ktime_get());
	spin_unlock_irqrestore(&dac33->lock, flags);

	/* Do not schedule the workqueue in Mode7 */
	if (dac33->fifo_mode != DAC33_FIFO_MODE7)
		schedule_work(&dac33->work);

	return IRQ_HANDLED;
}