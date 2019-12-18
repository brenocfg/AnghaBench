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
struct oxygen {unsigned int interrupt_mask; unsigned int pcm_running; int /*<<< orphan*/  ac97_waitqueue; TYPE_1__* midi; int /*<<< orphan*/  gpio_work; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  spdif_input_bits_work; scalar_t__* streams; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int OXYGEN_CHANNEL_A ; 
 unsigned int OXYGEN_CHANNEL_AC97 ; 
 unsigned int OXYGEN_CHANNEL_B ; 
 unsigned int OXYGEN_CHANNEL_C ; 
 unsigned int OXYGEN_CHANNEL_MULTICH ; 
 unsigned int OXYGEN_CHANNEL_SPDIF ; 
 int /*<<< orphan*/  OXYGEN_INTERRUPT_MASK ; 
 int /*<<< orphan*/  OXYGEN_INTERRUPT_STATUS ; 
 unsigned int OXYGEN_INT_AC97 ; 
 unsigned int OXYGEN_INT_GPIO ; 
 unsigned int OXYGEN_INT_MIDI ; 
 unsigned int OXYGEN_INT_SPDIF_IN_DETECT ; 
 int /*<<< orphan*/  OXYGEN_SPDIF_CONTROL ; 
 unsigned int OXYGEN_SPDIF_LOCK_INT ; 
 unsigned int OXYGEN_SPDIF_RATE_INT ; 
 unsigned int OXYGEN_SPDIF_SENSE_INT ; 
 unsigned int PCM_COUNT ; 
 unsigned int oxygen_read16 (struct oxygen*,int /*<<< orphan*/ ) ; 
 unsigned int oxygen_read32 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oxygen_read_uart (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  oxygen_write32 (struct oxygen*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t oxygen_interrupt(int dummy, void *dev_id)
{
	struct oxygen *chip = dev_id;
	unsigned int status, clear, elapsed_streams, i;

	status = oxygen_read16(chip, OXYGEN_INTERRUPT_STATUS);
	if (!status)
		return IRQ_NONE;

	spin_lock(&chip->reg_lock);

	clear = status & (OXYGEN_CHANNEL_A |
			  OXYGEN_CHANNEL_B |
			  OXYGEN_CHANNEL_C |
			  OXYGEN_CHANNEL_SPDIF |
			  OXYGEN_CHANNEL_MULTICH |
			  OXYGEN_CHANNEL_AC97 |
			  OXYGEN_INT_SPDIF_IN_DETECT |
			  OXYGEN_INT_GPIO |
			  OXYGEN_INT_AC97);
	if (clear) {
		if (clear & OXYGEN_INT_SPDIF_IN_DETECT)
			chip->interrupt_mask &= ~OXYGEN_INT_SPDIF_IN_DETECT;
		oxygen_write16(chip, OXYGEN_INTERRUPT_MASK,
			       chip->interrupt_mask & ~clear);
		oxygen_write16(chip, OXYGEN_INTERRUPT_MASK,
			       chip->interrupt_mask);
	}

	elapsed_streams = status & chip->pcm_running;

	spin_unlock(&chip->reg_lock);

	for (i = 0; i < PCM_COUNT; ++i)
		if ((elapsed_streams & (1 << i)) && chip->streams[i])
			snd_pcm_period_elapsed(chip->streams[i]);

	if (status & OXYGEN_INT_SPDIF_IN_DETECT) {
		spin_lock(&chip->reg_lock);
		i = oxygen_read32(chip, OXYGEN_SPDIF_CONTROL);
		if (i & (OXYGEN_SPDIF_SENSE_INT | OXYGEN_SPDIF_LOCK_INT |
			 OXYGEN_SPDIF_RATE_INT)) {
			/* write the interrupt bit(s) to clear */
			oxygen_write32(chip, OXYGEN_SPDIF_CONTROL, i);
			schedule_work(&chip->spdif_input_bits_work);
		}
		spin_unlock(&chip->reg_lock);
	}

	if (status & OXYGEN_INT_GPIO)
		schedule_work(&chip->gpio_work);

	if (status & OXYGEN_INT_MIDI) {
		if (chip->midi)
			snd_mpu401_uart_interrupt(0, chip->midi->private_data);
		else
			oxygen_read_uart(chip);
	}

	if (status & OXYGEN_INT_AC97)
		wake_up(&chip->ac97_waitqueue);

	return IRQ_HANDLED;
}