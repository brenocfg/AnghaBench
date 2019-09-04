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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct nuc900_audio {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ mmio; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct nuc900_audio* private_data; } ;

/* Variables and functions */
 scalar_t__ ACTL_CON ; 
 scalar_t__ ACTL_PSR ; 
 scalar_t__ ACTL_RSR ; 
 unsigned long AUDIO_READ (scalar_t__) ; 
 int /*<<< orphan*/  AUDIO_WRITE (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long P_DMA_END_IRQ ; 
 unsigned long P_DMA_MIDDLE_IRQ ; 
 unsigned long R_DMA_END_IRQ ; 
 unsigned long R_DMA_IRQ ; 
 unsigned long R_DMA_MIDDLE_IRQ ; 
 unsigned long T_DMA_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t nuc900_dma_interrupt(int irq, void *dev_id)
{
	struct snd_pcm_substream *substream = dev_id;
	struct nuc900_audio *nuc900_audio = substream->runtime->private_data;
	unsigned long val;

	spin_lock(&nuc900_audio->lock);

	val = AUDIO_READ(nuc900_audio->mmio + ACTL_CON);

	if (val & R_DMA_IRQ) {
		AUDIO_WRITE(nuc900_audio->mmio + ACTL_CON, val | R_DMA_IRQ);

		val = AUDIO_READ(nuc900_audio->mmio + ACTL_RSR);

		if (val & R_DMA_MIDDLE_IRQ) {
			val |= R_DMA_MIDDLE_IRQ;
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_RSR, val);
		}

		if (val & R_DMA_END_IRQ) {
			val |= R_DMA_END_IRQ;
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_RSR, val);
		}
	} else if (val & T_DMA_IRQ) {
		AUDIO_WRITE(nuc900_audio->mmio + ACTL_CON, val | T_DMA_IRQ);

		val = AUDIO_READ(nuc900_audio->mmio + ACTL_PSR);

		if (val & P_DMA_MIDDLE_IRQ) {
			val |= P_DMA_MIDDLE_IRQ;
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_PSR, val);
		}

		if (val & P_DMA_END_IRQ) {
			val |= P_DMA_END_IRQ;
			AUDIO_WRITE(nuc900_audio->mmio + ACTL_PSR, val);
		}
	} else {
		dev_err(nuc900_audio->dev, "Wrong DMA interrupt status!\n");
		spin_unlock(&nuc900_audio->lock);
		return IRQ_HANDLED;
	}

	spin_unlock(&nuc900_audio->lock);

	snd_pcm_period_elapsed(substream);

	return IRQ_HANDLED;
}