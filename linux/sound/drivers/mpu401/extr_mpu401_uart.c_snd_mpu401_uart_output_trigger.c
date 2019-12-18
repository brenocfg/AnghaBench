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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_mpu401 {int info_flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  output_lock; } ;
struct TYPE_2__ {struct snd_mpu401* private_data; } ;

/* Variables and functions */
 int MPU401_INFO_TX_IRQ ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_uart_add_timer (struct snd_mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mpu401_uart_output_write (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_mpu401_uart_remove_timer (struct snd_mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
snd_mpu401_uart_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct snd_mpu401 *mpu;

	mpu = substream->rmidi->private_data;
	if (up) {
		set_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode);

		/* try to add the timer at each output trigger,
		 * since the output timer might have been removed in
		 * snd_mpu401_uart_output_write().
		 */
		if (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
			snd_mpu401_uart_add_timer(mpu, 0);

		/* output pending data */
		spin_lock_irqsave(&mpu->output_lock, flags);
		snd_mpu401_uart_output_write(mpu);
		spin_unlock_irqrestore(&mpu->output_lock, flags);
	} else {
		if (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
			snd_mpu401_uart_remove_timer(mpu, 0);
		clear_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode);
	}
}