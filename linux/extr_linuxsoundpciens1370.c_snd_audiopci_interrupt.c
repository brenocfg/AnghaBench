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
struct ensoniq {unsigned int sctrl; scalar_t__ playback1_substream; scalar_t__ capture_substream; scalar_t__ playback2_substream; int /*<<< orphan*/  reg_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int ES_ADC ; 
 unsigned int ES_DAC1 ; 
 unsigned int ES_DAC2 ; 
 unsigned int ES_INTR ; 
 unsigned int ES_P1_INT_EN ; 
 unsigned int ES_P2_INT_EN ; 
 unsigned int ES_R1_INT_EN ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 unsigned int ES_UART ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SERIAL ; 
 int /*<<< orphan*/  STATUS ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ensoniq_midi_interrupt (struct ensoniq*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_audiopci_interrupt(int irq, void *dev_id)
{
	struct ensoniq *ensoniq = dev_id;
	unsigned int status, sctrl;

	if (ensoniq == NULL)
		return IRQ_NONE;

	status = inl(ES_REG(ensoniq, STATUS));
	if (!(status & ES_INTR))
		return IRQ_NONE;

	spin_lock(&ensoniq->reg_lock);
	sctrl = ensoniq->sctrl;
	if (status & ES_DAC1)
		sctrl &= ~ES_P1_INT_EN;
	if (status & ES_DAC2)
		sctrl &= ~ES_P2_INT_EN;
	if (status & ES_ADC)
		sctrl &= ~ES_R1_INT_EN;
	outl(sctrl, ES_REG(ensoniq, SERIAL));
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	spin_unlock(&ensoniq->reg_lock);

	if (status & ES_UART)
		snd_ensoniq_midi_interrupt(ensoniq);
	if ((status & ES_DAC2) && ensoniq->playback2_substream)
		snd_pcm_period_elapsed(ensoniq->playback2_substream);
	if ((status & ES_ADC) && ensoniq->capture_substream)
		snd_pcm_period_elapsed(ensoniq->capture_substream);
	if ((status & ES_DAC1) && ensoniq->playback1_substream)
		snd_pcm_period_elapsed(ensoniq->playback1_substream);
	return IRQ_HANDLED;
}