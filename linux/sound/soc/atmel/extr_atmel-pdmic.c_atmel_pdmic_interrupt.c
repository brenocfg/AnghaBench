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
typedef  int u32 ;
struct atmel_pdmic {int /*<<< orphan*/  substream; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PDMIC_CR ; 
 int PDMIC_CR_ENPDM_DIS ; 
 int /*<<< orphan*/  PDMIC_CR_ENPDM_MASK ; 
 int PDMIC_CR_ENPDM_SHIFT ; 
 int /*<<< orphan*/  PDMIC_ISR ; 
 int PDMIC_ISR_OVRE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t atmel_pdmic_interrupt(int irq, void *dev_id)
{
	struct atmel_pdmic *dd = (struct atmel_pdmic *)dev_id;
	u32 pdmic_isr;
	irqreturn_t ret = IRQ_NONE;

	regmap_read(dd->regmap, PDMIC_ISR, &pdmic_isr);

	if (pdmic_isr & PDMIC_ISR_OVRE) {
		regmap_update_bits(dd->regmap, PDMIC_CR, PDMIC_CR_ENPDM_MASK,
				   PDMIC_CR_ENPDM_DIS << PDMIC_CR_ENPDM_SHIFT);

		snd_pcm_stop_xrun(dd->substream);

		ret = IRQ_HANDLED;
	}

	return ret;
}