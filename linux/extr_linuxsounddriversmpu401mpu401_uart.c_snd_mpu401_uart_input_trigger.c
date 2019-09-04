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
struct snd_mpu401 {int info_flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  (* read ) (struct snd_mpu401*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct snd_mpu401* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401D (struct snd_mpu401*) ; 
 int MPU401_INFO_USE_TIMER ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_INPUT_TRIGGER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mpu401_uart_add_timer (struct snd_mpu401*,int) ; 
 int /*<<< orphan*/  snd_mpu401_uart_input_read (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_mpu401_uart_remove_timer (struct snd_mpu401*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_mpu401*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snd_mpu401_uart_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct snd_mpu401 *mpu;
	int max = 64;

	mpu = substream->rmidi->private_data;
	if (up) {
		if (! test_and_set_bit(MPU401_MODE_BIT_INPUT_TRIGGER,
				       &mpu->mode)) {
			/* first time - flush FIFO */
			while (max-- > 0)
				mpu->read(mpu, MPU401D(mpu));
			if (mpu->info_flags & MPU401_INFO_USE_TIMER)
				snd_mpu401_uart_add_timer(mpu, 1);
		}
		
		/* read data in advance */
		spin_lock_irqsave(&mpu->input_lock, flags);
		snd_mpu401_uart_input_read(mpu);
		spin_unlock_irqrestore(&mpu->input_lock, flags);
	} else {
		if (mpu->info_flags & MPU401_INFO_USE_TIMER)
			snd_mpu401_uart_remove_timer(mpu, 1);
		clear_bit(MPU401_MODE_BIT_INPUT_TRIGGER, &mpu->mode);
	}

}