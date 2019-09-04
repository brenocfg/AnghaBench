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
struct snd_uart16550 {scalar_t__ filemode; int /*<<< orphan*/  open_lock; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ SERIAL_MODE_NOT_OPENED ; 
 scalar_t__ UART_IIR ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  snd_uart16550_io_loop (struct snd_uart16550*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_uart16550_interrupt(int irq, void *dev_id)
{
	struct snd_uart16550 *uart;

	uart = dev_id;
	spin_lock(&uart->open_lock);
	if (uart->filemode == SERIAL_MODE_NOT_OPENED) {
		spin_unlock(&uart->open_lock);
		return IRQ_NONE;
	}
	/* indicate to the UART that the interrupt has been serviced */
	inb(uart->base + UART_IIR);
	snd_uart16550_io_loop(uart);
	spin_unlock(&uart->open_lock);
	return IRQ_HANDLED;
}