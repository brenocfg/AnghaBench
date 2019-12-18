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
typedef  int u32 ;
struct snd_ymfpci_voice {int /*<<< orphan*/  (* interrupt ) (struct snd_ymfpci*,struct snd_ymfpci_voice*) ;} ;
struct snd_ymfpci {int active_bank; TYPE_1__* rawmidi; int /*<<< orphan*/  timer_ticks; scalar_t__ timer; int /*<<< orphan*/  interrupt_sleep; int /*<<< orphan*/  interrupt_sleep_count; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  voice_lock; scalar_t__* effect_substream; scalar_t__* capture_substream; struct snd_ymfpci_voice* voices; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  YDSXGR_CTRLSELECT ; 
 int /*<<< orphan*/  YDSXGR_INTFLAG ; 
 int /*<<< orphan*/  YDSXGR_MODE ; 
 int /*<<< orphan*/  YDSXGR_STATUS ; 
 int YDSXG_CAPTURE_VOICES ; 
 int YDSXG_EFFECT_VOICES ; 
 int YDSXG_PLAYBACK_VOICES ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_interrupt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_pcm_capture_interrupt (scalar_t__) ; 
 int /*<<< orphan*/  snd_ymfpci_pcm_effect_interrupt (scalar_t__) ; 
 int snd_ymfpci_readl (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int snd_ymfpci_readw (struct snd_ymfpci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ymfpci_writel (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_ymfpci_writew (struct snd_ymfpci*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_ymfpci*,struct snd_ymfpci_voice*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_ymfpci_interrupt(int irq, void *dev_id)
{
	struct snd_ymfpci *chip = dev_id;
	u32 status, nvoice, mode;
	struct snd_ymfpci_voice *voice;

	status = snd_ymfpci_readl(chip, YDSXGR_STATUS);
	if (status & 0x80000000) {
		chip->active_bank = snd_ymfpci_readl(chip, YDSXGR_CTRLSELECT) & 1;
		spin_lock(&chip->voice_lock);
		for (nvoice = 0; nvoice < YDSXG_PLAYBACK_VOICES; nvoice++) {
			voice = &chip->voices[nvoice];
			if (voice->interrupt)
				voice->interrupt(chip, voice);
		}
		for (nvoice = 0; nvoice < YDSXG_CAPTURE_VOICES; nvoice++) {
			if (chip->capture_substream[nvoice])
				snd_ymfpci_pcm_capture_interrupt(chip->capture_substream[nvoice]);
		}
#if 0
		for (nvoice = 0; nvoice < YDSXG_EFFECT_VOICES; nvoice++) {
			if (chip->effect_substream[nvoice])
				snd_ymfpci_pcm_effect_interrupt(chip->effect_substream[nvoice]);
		}
#endif
		spin_unlock(&chip->voice_lock);
		spin_lock(&chip->reg_lock);
		snd_ymfpci_writel(chip, YDSXGR_STATUS, 0x80000000);
		mode = snd_ymfpci_readl(chip, YDSXGR_MODE) | 2;
		snd_ymfpci_writel(chip, YDSXGR_MODE, mode);
		spin_unlock(&chip->reg_lock);

		if (atomic_read(&chip->interrupt_sleep_count)) {
			atomic_set(&chip->interrupt_sleep_count, 0);
			wake_up(&chip->interrupt_sleep);
		}
	}

	status = snd_ymfpci_readw(chip, YDSXGR_INTFLAG);
	if (status & 1) {
		if (chip->timer)
			snd_timer_interrupt(chip->timer, chip->timer_ticks);
	}
	snd_ymfpci_writew(chip, YDSXGR_INTFLAG, status);

	if (chip->rawmidi)
		snd_mpu401_uart_interrupt(irq, chip->rawmidi->private_data);
	return IRQ_HANDLED;
}