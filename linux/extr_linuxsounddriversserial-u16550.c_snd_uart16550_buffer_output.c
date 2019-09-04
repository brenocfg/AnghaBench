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
struct snd_uart16550 {unsigned short buff_out; scalar_t__ buff_in_count; int /*<<< orphan*/  fifo_count; scalar_t__ base; int /*<<< orphan*/ * tx_buff; } ;

/* Variables and functions */
 unsigned short TX_BUFF_MASK ; 
 scalar_t__ UART_TX ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void snd_uart16550_buffer_output(struct snd_uart16550 *uart)
{
	unsigned short buff_out = uart->buff_out;
	if (uart->buff_in_count > 0) {
		outb(uart->tx_buff[buff_out], uart->base + UART_TX);
		uart->fifo_count++;
		buff_out++;
		buff_out &= TX_BUFF_MASK;
		uart->buff_out = buff_out;
		uart->buff_in_count--;
	}
}