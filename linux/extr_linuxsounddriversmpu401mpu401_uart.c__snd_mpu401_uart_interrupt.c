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
struct snd_mpu401 {int info_flags; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int MPU401_INFO_INPUT ; 
 int MPU401_INFO_TX_IRQ ; 
 int /*<<< orphan*/  MPU401_MODE_BIT_INPUT ; 
 int /*<<< orphan*/  snd_mpu401_uart_clear_rx (struct snd_mpu401*) ; 
 int /*<<< orphan*/  snd_mpu401_uart_input_read (struct snd_mpu401*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_interrupt_tx (struct snd_mpu401*) ; 

__attribute__((used)) static void _snd_mpu401_uart_interrupt(struct snd_mpu401 *mpu)
{
	unsigned long flags;

	if (mpu->info_flags & MPU401_INFO_INPUT) {
		spin_lock_irqsave(&mpu->input_lock, flags);
		if (test_bit(MPU401_MODE_BIT_INPUT, &mpu->mode))
			snd_mpu401_uart_input_read(mpu);
		else
			snd_mpu401_uart_clear_rx(mpu);
		spin_unlock_irqrestore(&mpu->input_lock, flags);
	}
	if (! (mpu->info_flags & MPU401_INFO_TX_IRQ))
		/* ok. for better Tx performance try do some output
		   when input is done */
		uart_interrupt_tx(mpu);
}