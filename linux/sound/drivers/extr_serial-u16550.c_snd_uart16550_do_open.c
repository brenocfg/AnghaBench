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
struct snd_uart16550 {int fifo_limit; char divisor; int old_line_ctrl_reg; int old_divisor_lsb; int old_divisor_msb; int adaptor; scalar_t__ irq; scalar_t__ base; scalar_t__ timer_running; scalar_t__ fifo_count; scalar_t__ buff_out; scalar_t__ buff_in; scalar_t__ buff_in_count; } ;

/* Variables and functions */
 int const SNDRV_SERIAL_GENERIC ; 
#define  SNDRV_SERIAL_MS124T 130 
#define  SNDRV_SERIAL_MS124W_MB 129 
#define  SNDRV_SERIAL_MS124W_SA 128 
 scalar_t__ UART_DLL ; 
 scalar_t__ UART_DLM ; 
 scalar_t__ UART_FCR ; 
 char UART_FCR_CLEAR_RCVR ; 
 char UART_FCR_CLEAR_XMIT ; 
 char UART_FCR_ENABLE_FIFO ; 
 char UART_FCR_TRIGGER_4 ; 
 scalar_t__ UART_IER ; 
 char UART_IER_MSI ; 
 char UART_IER_RDI ; 
 char UART_IER_THRI ; 
 scalar_t__ UART_IIR ; 
 scalar_t__ UART_LCR ; 
 char UART_LCR_DLAB ; 
 char UART_LCR_WLEN8 ; 
 scalar_t__ UART_LSR ; 
 scalar_t__ UART_MCR ; 
 char UART_MCR_DTR ; 
 char UART_MCR_OUT2 ; 
 char UART_MCR_RTS ; 
 scalar_t__ UART_RX ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (char,scalar_t__) ; 

__attribute__((used)) static void snd_uart16550_do_open(struct snd_uart16550 * uart)
{
	char byte;

	/* Initialize basic variables */
	uart->buff_in_count = 0;
	uart->buff_in = 0;
	uart->buff_out = 0;
	uart->fifo_limit = 1;
	uart->fifo_count = 0;
	uart->timer_running = 0;

	outb(UART_FCR_ENABLE_FIFO	/* Enable FIFO's (if available) */
	     | UART_FCR_CLEAR_RCVR	/* Clear receiver FIFO */
	     | UART_FCR_CLEAR_XMIT	/* Clear transmitter FIFO */
	     | UART_FCR_TRIGGER_4	/* Set FIFO trigger at 4-bytes */
	/* NOTE: interrupt generated after T=(time)4-bytes
	 * if less than UART_FCR_TRIGGER bytes received
	 */
	     ,uart->base + UART_FCR);	/* FIFO Control Register */

	if ((inb(uart->base + UART_IIR) & 0xf0) == 0xc0)
		uart->fifo_limit = 16;
	if (uart->divisor != 0) {
		uart->old_line_ctrl_reg = inb(uart->base + UART_LCR);
		outb(UART_LCR_DLAB	/* Divisor latch access bit */
		     ,uart->base + UART_LCR);	/* Line Control Register */
		uart->old_divisor_lsb = inb(uart->base + UART_DLL);
		uart->old_divisor_msb = inb(uart->base + UART_DLM);

		outb(uart->divisor
		     ,uart->base + UART_DLL);	/* Divisor Latch Low */
		outb(0
		     ,uart->base + UART_DLM);	/* Divisor Latch High */
		/* DLAB is reset to 0 in next outb() */
	}
	/* Set serial parameters (parity off, etc) */
	outb(UART_LCR_WLEN8	/* 8 data-bits */
	     | 0		/* 1 stop-bit */
	     | 0		/* parity off */
	     | 0		/* DLAB = 0 */
	     ,uart->base + UART_LCR);	/* Line Control Register */

	switch (uart->adaptor) {
	default:
		outb(UART_MCR_RTS	/* Set Request-To-Send line active */
		     | UART_MCR_DTR	/* Set Data-Terminal-Ready line active */
		     | UART_MCR_OUT2	/* Set OUT2 - not always required, but when
					 * it is, it is ESSENTIAL for enabling interrupts
				 */
		     ,uart->base + UART_MCR);	/* Modem Control Register */
		break;
	case SNDRV_SERIAL_MS124W_SA:
	case SNDRV_SERIAL_MS124W_MB:
		/* MS-124W can draw power from RTS and DTR if they
		   are in opposite states. */ 
		outb(UART_MCR_RTS | (0&UART_MCR_DTR) | UART_MCR_OUT2,
		     uart->base + UART_MCR);
		break;
	case SNDRV_SERIAL_MS124T:
		/* MS-124T can draw power from RTS and/or DTR (preferably
		   both) if they are both asserted. */
		outb(UART_MCR_RTS | UART_MCR_DTR | UART_MCR_OUT2,
		     uart->base + UART_MCR);
		break;
	}

	if (uart->irq < 0) {
		byte = (0 & UART_IER_RDI)	/* Disable Receiver data interrupt */
		    |(0 & UART_IER_THRI)	/* Disable Transmitter holding register empty interrupt */
		    ;
	} else if (uart->adaptor == SNDRV_SERIAL_MS124W_SA) {
		byte = UART_IER_RDI	/* Enable Receiver data interrupt */
		    | UART_IER_MSI	/* Enable Modem status interrupt */
		    ;
	} else if (uart->adaptor == SNDRV_SERIAL_GENERIC) {
		byte = UART_IER_RDI	/* Enable Receiver data interrupt */
		    | UART_IER_MSI	/* Enable Modem status interrupt */
		    | UART_IER_THRI	/* Enable Transmitter holding register empty interrupt */
		    ;
	} else {
		byte = UART_IER_RDI	/* Enable Receiver data interrupt */
		    | UART_IER_THRI	/* Enable Transmitter holding register empty interrupt */
		    ;
	}
	outb(byte, uart->base + UART_IER);	/* Interrupt enable Register */

	inb(uart->base + UART_LSR);	/* Clear any pre-existing overrun indication */
	inb(uart->base + UART_IIR);	/* Clear any pre-existing transmit interrupt */
	inb(uart->base + UART_RX);	/* Clear any pre-existing receive interrupt */
}