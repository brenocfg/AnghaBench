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
struct snd_pcm_runtime {int channels; scalar_t__ dma_area; } ;
struct cmipci_pcm {int ch; scalar_t__ needs_silencing; TYPE_1__* substream; } ;
struct cmipci {int ctrl; int /*<<< orphan*/  reg_lock; scalar_t__ can_96k; } ;
struct TYPE_2__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int CM_ASFC_MASK ; 
 int CM_ASFC_SHIFT ; 
 int CM_CH0FMT_MASK ; 
 int CM_CH0FMT_SHIFT ; 
 int CM_CH0_SRATE_MASK ; 
 int CM_CHEN0 ; 
 unsigned int CM_REG_CH0_FRAME2 ; 
 unsigned int CM_REG_CH1_FRAME2 ; 
 unsigned int CM_REG_CHFORMAT ; 
 unsigned int CM_REG_FUNCTRL0 ; 
 unsigned int CM_REG_FUNCTRL1 ; 
 unsigned int CM_RST_CH0 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_dac_channels (struct cmipci*,struct cmipci_pcm*,int) ; 
 unsigned int snd_cmipci_read (struct cmipci*,unsigned int) ; 
 int /*<<< orphan*/  snd_cmipci_write (struct cmipci*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_cmipci_silence_hack(struct cmipci *cm, struct cmipci_pcm *rec)
{
	struct snd_pcm_runtime *runtime = rec->substream->runtime;
	unsigned int reg, val;

	if (rec->needs_silencing && runtime && runtime->dma_area) {
		/* set up a small silence buffer */
		memset(runtime->dma_area, 0, PAGE_SIZE);
		reg = rec->ch ? CM_REG_CH1_FRAME2 : CM_REG_CH0_FRAME2;
		val = ((PAGE_SIZE / 4) - 1) | (((PAGE_SIZE / 4) / 2 - 1) << 16);
		snd_cmipci_write(cm, reg, val);
	
		/* configure for 16 bits, 2 channels, 8 kHz */
		if (runtime->channels > 2)
			set_dac_channels(cm, rec, 2);
		spin_lock_irq(&cm->reg_lock);
		val = snd_cmipci_read(cm, CM_REG_FUNCTRL1);
		val &= ~(CM_ASFC_MASK << (rec->ch * 3));
		val |= (4 << CM_ASFC_SHIFT) << (rec->ch * 3);
		snd_cmipci_write(cm, CM_REG_FUNCTRL1, val);
		val = snd_cmipci_read(cm, CM_REG_CHFORMAT);
		val &= ~(CM_CH0FMT_MASK << (rec->ch * 2));
		val |= (3 << CM_CH0FMT_SHIFT) << (rec->ch * 2);
		if (cm->can_96k)
			val &= ~(CM_CH0_SRATE_MASK << (rec->ch * 2));
		snd_cmipci_write(cm, CM_REG_CHFORMAT, val);
	
		/* start stream (we don't need interrupts) */
		cm->ctrl |= CM_CHEN0 << rec->ch;
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl);
		spin_unlock_irq(&cm->reg_lock);

		msleep(1);

		/* stop and reset stream */
		spin_lock_irq(&cm->reg_lock);
		cm->ctrl &= ~(CM_CHEN0 << rec->ch);
		val = CM_RST_CH0 << rec->ch;
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl | val);
		snd_cmipci_write(cm, CM_REG_FUNCTRL0, cm->ctrl & ~val);
		spin_unlock_irq(&cm->reg_lock);

		rec->needs_silencing = 0;
	}
}