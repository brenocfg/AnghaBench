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
typedef  int u8 ;
struct snd_soc_component {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DA7218_EVENT ; 
 int DA7218_HPLDET_JACK_EVENT_MASK ; 
 int DA7218_LVL_DET_EVENT_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  da7218_hpldet_irq (struct snd_soc_component*) ; 
 int /*<<< orphan*/  da7218_micldet_irq (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t da7218_irq_thread(int irq, void *data)
{
	struct snd_soc_component *component = data;
	u8 status;

	/* Read IRQ status reg */
	status = snd_soc_component_read32(component, DA7218_EVENT);
	if (!status)
		return IRQ_NONE;

	/* Mic level detect */
	if (status & DA7218_LVL_DET_EVENT_MASK)
		da7218_micldet_irq(component);

	/* HP detect */
	if (status & DA7218_HPLDET_JACK_EVENT_MASK)
		da7218_hpldet_irq(component);

	/* Clear interrupts */
	snd_soc_component_write(component, DA7218_EVENT, status);

	return IRQ_HANDLED;
}