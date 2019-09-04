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
struct uart_port {int uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; scalar_t__ fifosize; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CLOCAL ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 
 unsigned int* CSR_H_UBRLCR ; 
 unsigned int* CSR_L_UBRLCR ; 
 unsigned int* CSR_M_UBRLCR ; 
 int* CSR_UARTCON ; 
 int CSTOPB ; 
 int HUPCL ; 
 unsigned int H_UBRLCR_FIFO ; 
 unsigned int H_UBRLCR_PARENB ; 
 unsigned int H_UBRLCR_PAREVN ; 
 unsigned int H_UBRLCR_STOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARODD ; 
 int RXSTAT_DUMMY_READ ; 
 int RXSTAT_FRAME ; 
 int RXSTAT_OVERRUN ; 
 int RXSTAT_PARITY ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
serial21285_set_termios(struct uart_port *port, struct ktermios *termios,
			struct ktermios *old)
{
	unsigned long flags;
	unsigned int baud, quot, h_lcr, b;

	/*
	 * We don't support modem control lines.
	 */
	termios->c_cflag &= ~(HUPCL | CRTSCTS | CMSPAR);
	termios->c_cflag |= CLOCAL;

	/*
	 * We don't support BREAK character recognition.
	 */
	termios->c_iflag &= ~(IGNBRK | BRKINT);

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16); 
	quot = uart_get_divisor(port, baud);
	b = port->uartclk / (16 * quot);
	tty_termios_encode_baud_rate(termios, b, b);

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		h_lcr = 0x00;
		break;
	case CS6:
		h_lcr = 0x20;
		break;
	case CS7:
		h_lcr = 0x40;
		break;
	default: /* CS8 */
		h_lcr = 0x60;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		h_lcr |= H_UBRLCR_STOPB;
	if (termios->c_cflag & PARENB) {
		h_lcr |= H_UBRLCR_PARENB;
		if (!(termios->c_cflag & PARODD))
			h_lcr |= H_UBRLCR_PAREVN;
	}

	if (port->fifosize)
		h_lcr |= H_UBRLCR_FIFO;

	spin_lock_irqsave(&port->lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	/*
	 * Which character status flags are we interested in?
	 */
	port->read_status_mask = RXSTAT_OVERRUN;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= RXSTAT_FRAME | RXSTAT_PARITY;

	/*
	 * Which character status flags should we ignore?
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= RXSTAT_FRAME | RXSTAT_PARITY;
	if (termios->c_iflag & IGNBRK && termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= RXSTAT_OVERRUN;

	/*
	 * Ignore all characters if CREAD is not set.
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= RXSTAT_DUMMY_READ;

	quot -= 1;

	*CSR_UARTCON = 0;
	*CSR_L_UBRLCR = quot & 0xff;
	*CSR_M_UBRLCR = (quot >> 8) & 0x0f;
	*CSR_H_UBRLCR = h_lcr;
	*CSR_UARTCON = 1;

	spin_unlock_irqrestore(&port->lock, flags);
}