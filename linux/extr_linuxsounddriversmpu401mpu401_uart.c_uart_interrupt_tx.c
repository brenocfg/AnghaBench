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
struct snd_mpu401 {int /*<<< orphan*/  output_lock; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU401_MODE_BIT_OUTPUT ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_OUTPUT_TRIGGER ; 
 int /*<<< orphan*/  snd_mpu401_uart_output_write (struct snd_mpu401*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uart_interrupt_tx(struct snd_mpu401 *mpu)
{
	unsigned long flags;

	if (test_bit(MPU401_MODE_BIT_OUTPUT, &mpu->mode) &&
	    test_bit(MPU401_MODE_BIT_OUTPUT_TRIGGER, &mpu->mode)) {
		spin_lock_irqsave(&mpu->output_lock, flags);
		snd_mpu401_uart_output_write(mpu);
		spin_unlock_irqrestore(&mpu->output_lock, flags);
	}
}