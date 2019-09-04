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
struct snd_uart16550 {scalar_t__ irq; int adaptor; scalar_t__ divisor; int old_divisor_lsb; int old_divisor_msb; int old_line_ctrl_reg; scalar_t__ base; } ;

/* Variables and functions */
#define  SNDRV_SERIAL_MS124T 130 
#define  SNDRV_SERIAL_MS124W_MB 129 
#define  SNDRV_SERIAL_MS124W_SA 128 
 scalar_t__ UART_DLL ; 
 scalar_t__ UART_DLM ; 
 scalar_t__ UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_THRI ; 
 scalar_t__ UART_IIR ; 
 scalar_t__ UART_LCR ; 
 int UART_LCR_DLAB ; 
 scalar_t__ UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  snd_uart16550_del_timer (struct snd_uart16550*) ; 

__attribute__((used)) static void snd_uart16550_do_close(struct snd_uart16550 * uart)
{
	if (uart->irq < 0)
		snd_uart16550_del_timer(uart);

	/* NOTE: may need to disable interrupts before de-registering out handler.
	 * For now, the consequences are harmless.
	 */

	outb((0 & UART_IER_RDI)		/* Disable Receiver data interrupt */
	     |(0 & UART_IER_THRI)	/* Disable Transmitter holding register empty interrupt */
	     ,uart->base + UART_IER);	/* Interrupt enable Register */

	switch (uart->adaptor) {
	default:
		outb((0 & UART_MCR_RTS)		/* Deactivate Request-To-Send line  */
		     |(0 & UART_MCR_DTR)	/* Deactivate Data-Terminal-Ready line */
		     |(0 & UART_MCR_OUT2)	/* Deactivate OUT2 */
		     ,uart->base + UART_MCR);	/* Modem Control Register */
	  break;
	case SNDRV_SERIAL_MS124W_SA:
	case SNDRV_SERIAL_MS124W_MB:
		/* MS-124W can draw power from RTS and DTR if they
		   are in opposite states; leave it powered. */ 
		outb(UART_MCR_RTS | (0&UART_MCR_DTR) | (0&UART_MCR_OUT2),
		     uart->base + UART_MCR);
		break;
	case SNDRV_SERIAL_MS124T:
		/* MS-124T can draw power from RTS and/or DTR (preferably
		   both) if they are both asserted; leave it powered. */
		outb(UART_MCR_RTS | UART_MCR_DTR | (0&UART_MCR_OUT2),
		     uart->base + UART_MCR);
		break;
	}

	inb(uart->base + UART_IIR);	/* Clear any outstanding interrupts */

	/* Restore old divisor */
	if (uart->divisor != 0) {
		outb(UART_LCR_DLAB		/* Divisor latch access bit */
		     ,uart->base + UART_LCR);	/* Line Control Register */
		outb(uart->old_divisor_lsb
		     ,uart->base + UART_DLL);	/* Divisor Latch Low */
		outb(uart->old_divisor_msb
		     ,uart->base + UART_DLM);	/* Divisor Latch High */
		/* Restore old LCR (data bits, stop bits, parity, DLAB) */
		outb(uart->old_line_ctrl_reg
		     ,uart->base + UART_LCR);	/* Line Control Register */
	}
}