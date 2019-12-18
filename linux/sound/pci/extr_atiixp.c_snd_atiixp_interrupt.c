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
struct atiixp {unsigned int codec_not_ready_bits; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * dmas; int /*<<< orphan*/  spdif_over_aclink; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t ATI_DMA_CAPTURE ; 
 size_t ATI_DMA_PLAYBACK ; 
 size_t ATI_DMA_SPDIF ; 
 unsigned int ATI_REG_ISR_IN_STATUS ; 
 unsigned int ATI_REG_ISR_IN_XRUN ; 
 unsigned int ATI_REG_ISR_OUT_STATUS ; 
 unsigned int ATI_REG_ISR_OUT_XRUN ; 
 unsigned int ATI_REG_ISR_SPDF_STATUS ; 
 unsigned int ATI_REG_ISR_SPDF_XRUN ; 
 unsigned int CODEC_CHECK_BITS ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  ISR ; 
 unsigned int atiixp_read (struct atiixp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_atiixp_update_dma (struct atiixp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_atiixp_xrun_dma (struct atiixp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_atiixp_interrupt(int irq, void *dev_id)
{
	struct atiixp *chip = dev_id;
	unsigned int status;

	status = atiixp_read(chip, ISR);

	if (! status)
		return IRQ_NONE;

	/* process audio DMA */
	if (status & ATI_REG_ISR_OUT_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_PLAYBACK]);
	else if (status & ATI_REG_ISR_OUT_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_PLAYBACK]);
	if (status & ATI_REG_ISR_IN_XRUN)
		snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_CAPTURE]);
	else if (status & ATI_REG_ISR_IN_STATUS)
		snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_CAPTURE]);
	if (! chip->spdif_over_aclink) {
		if (status & ATI_REG_ISR_SPDF_XRUN)
			snd_atiixp_xrun_dma(chip,  &chip->dmas[ATI_DMA_SPDIF]);
		else if (status & ATI_REG_ISR_SPDF_STATUS)
			snd_atiixp_update_dma(chip, &chip->dmas[ATI_DMA_SPDIF]);
	}

	/* for codec detection */
	if (status & CODEC_CHECK_BITS) {
		unsigned int detected;
		detected = status & CODEC_CHECK_BITS;
		spin_lock(&chip->reg_lock);
		chip->codec_not_ready_bits |= detected;
		atiixp_update(chip, IER, detected, 0); /* disable the detected irqs */
		spin_unlock(&chip->reg_lock);
	}

	/* ack */
	atiixp_write(chip, ISR, status);

	return IRQ_HANDLED;
}