#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snd_azf3328 {TYPE_2__* card; TYPE_1__* rmidi; int /*<<< orphan*/  codecs; int /*<<< orphan*/  reg_lock; TYPE_3__* timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  sticks; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDX_IO_IRQSTATUS ; 
 scalar_t__ IDX_IO_TIMER_VALUE ; 
 int IRQ_GAMEPORT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IRQ_I2S_OUT ; 
 int IRQ_MPU401 ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int IRQ_PLAYBACK ; 
 int IRQ_RECORDING ; 
 int IRQ_TIMER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int snd_azf3328_ctrl_inb (struct snd_azf3328*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_azf3328_ctrl_outb (struct snd_azf3328*,scalar_t__,int) ; 
 int /*<<< orphan*/  snd_azf3328_gameport_interrupt (struct snd_azf3328*) ; 
 int /*<<< orphan*/  snd_azf3328_pcm_interrupt (struct snd_azf3328*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_timer_interrupt (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
snd_azf3328_interrupt(int irq, void *dev_id)
{
	struct snd_azf3328 *chip = dev_id;
	u8 status;
	static unsigned long irq_count;

	status = snd_azf3328_ctrl_inb(chip, IDX_IO_IRQSTATUS);

        /* fast path out, to ease interrupt sharing */
	if (!(status &
		(IRQ_PLAYBACK|IRQ_RECORDING|IRQ_I2S_OUT
		|IRQ_GAMEPORT|IRQ_MPU401|IRQ_TIMER)
	))
		return IRQ_NONE; /* must be interrupt for another device */

	dev_dbg(chip->card->dev,
		"irq_count %ld! IDX_IO_IRQSTATUS %04x\n",
			irq_count++ /* debug-only */,
			status);

	if (status & IRQ_TIMER) {
		/* dev_dbg(chip->card->dev, "timer %ld\n",
			snd_azf3328_codec_inl(chip, IDX_IO_TIMER_VALUE)
				& TIMER_VALUE_MASK
		); */
		if (chip->timer)
			snd_timer_interrupt(chip->timer, chip->timer->sticks);
		/* ACK timer */
                spin_lock(&chip->reg_lock);
		snd_azf3328_ctrl_outb(chip, IDX_IO_TIMER_VALUE + 3, 0x07);
		spin_unlock(&chip->reg_lock);
		dev_dbg(chip->card->dev, "timer IRQ\n");
	}

	if (status & (IRQ_PLAYBACK|IRQ_RECORDING|IRQ_I2S_OUT))
		snd_azf3328_pcm_interrupt(chip, chip->codecs, status);

	if (status & IRQ_GAMEPORT)
		snd_azf3328_gameport_interrupt(chip);

	/* MPU401 has less critical IRQ requirements
	 * than timer and playback/recording, right? */
	if (status & IRQ_MPU401) {
		snd_mpu401_uart_interrupt(irq, chip->rmidi->private_data);

		/* hmm, do we have to ack the IRQ here somehow?
		 * If so, then I don't know how yet... */
		dev_dbg(chip->card->dev, "MPU401 IRQ\n");
	}
	return IRQ_HANDLED;
}