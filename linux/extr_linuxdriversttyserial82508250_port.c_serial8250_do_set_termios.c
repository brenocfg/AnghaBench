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
struct uart_port {int fifosize; int read_status_mask; int ignore_status_mask; int flags; scalar_t__ type; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_8250_port {int capabilities; unsigned char lcr; int fcr; int ier; int bugs; int /*<<< orphan*/  port; int /*<<< orphan*/  mcr; scalar_t__ fifo_bug; int /*<<< orphan*/  dma; } ;
struct ktermios {int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
 int CS5 ; 
 int CS6 ; 
 int CS7 ; 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 scalar_t__ PORT_16750 ; 
 int UART_BUG_NOMSR ; 
 int UART_CAP_AFE ; 
 int UART_CAP_EFR ; 
 int UART_CAP_FIFO ; 
 int UART_CAP_MINI ; 
 int UART_CAP_RTOIE ; 
 int UART_CAP_UUE ; 
 int /*<<< orphan*/  UART_EFR ; 
 unsigned char UART_EFR_CTS ; 
 scalar_t__ UART_ENABLE_MS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_FCR_TRIGGER_1 ; 
 int UART_FCR_TRIGGER_MASK ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_MSI ; 
 int UART_IER_RTOIE ; 
 int UART_IER_UUE ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_CONF_MODE_B ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_MCR_AFE ; 
 int /*<<< orphan*/  UART_XR_EFR ; 
 int UPF_EXAR_EFR ; 
 unsigned char serial8250_compute_lcr (struct uart_8250_port*,int) ; 
 unsigned int serial8250_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 unsigned int serial8250_get_divisor (struct uart_port*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  serial8250_rpm_get (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_rpm_put (struct uart_8250_port*) ; 
 int /*<<< orphan*/  serial8250_set_divisor (struct uart_port*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  serial8250_set_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

void
serial8250_do_set_termios(struct uart_port *port, struct ktermios *termios,
			  struct ktermios *old)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned char cval;
	unsigned long flags;
	unsigned int baud, quot, frac = 0;

	if (up->capabilities & UART_CAP_MINI) {
		termios->c_cflag &= ~(CSTOPB | PARENB | PARODD | CMSPAR);
		if ((termios->c_cflag & CSIZE) == CS5 ||
		    (termios->c_cflag & CSIZE) == CS6)
			termios->c_cflag = (termios->c_cflag & ~CSIZE) | CS7;
	}
	cval = serial8250_compute_lcr(up, termios->c_cflag);

	baud = serial8250_get_baud_rate(port, termios, old);
	quot = serial8250_get_divisor(port, baud, &frac);

	/*
	 * Ok, we're now changing the port state.  Do it with
	 * interrupts disabled.
	 */
	serial8250_rpm_get(up);
	spin_lock_irqsave(&port->lock, flags);

	up->lcr = cval;					/* Save computed LCR */

	if (up->capabilities & UART_CAP_FIFO && port->fifosize > 1) {
		/* NOTE: If fifo_bug is not set, a user can set RX_trigger. */
		if ((baud < 2400 && !up->dma) || up->fifo_bug) {
			up->fcr &= ~UART_FCR_TRIGGER_MASK;
			up->fcr |= UART_FCR_TRIGGER_1;
		}
	}

	/*
	 * MCR-based auto flow control.  When AFE is enabled, RTS will be
	 * deasserted when the receive FIFO contains more characters than
	 * the trigger, or the MCR RTS bit is cleared.
	 */
	if (up->capabilities & UART_CAP_AFE) {
		up->mcr &= ~UART_MCR_AFE;
		if (termios->c_cflag & CRTSCTS)
			up->mcr |= UART_MCR_AFE;
	}

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	port->read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (termios->c_iflag & INPCK)
		port->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= UART_LSR_BI;

	/*
	 * Characteres to ignore
	 */
	port->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		port->ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (termios->c_iflag & IGNBRK) {
		port->ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			port->ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		port->ignore_status_mask |= UART_LSR_DR;

	/*
	 * CTS flow control flag and modem status interrupts
	 */
	up->ier &= ~UART_IER_MSI;
	if (!(up->bugs & UART_BUG_NOMSR) &&
			UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;
	if (up->capabilities & UART_CAP_UUE)
		up->ier |= UART_IER_UUE;
	if (up->capabilities & UART_CAP_RTOIE)
		up->ier |= UART_IER_RTOIE;

	serial_port_out(port, UART_IER, up->ier);

	if (up->capabilities & UART_CAP_EFR) {
		unsigned char efr = 0;
		/*
		 * TI16C752/Startech hardware flow control.  FIXME:
		 * - TI16C752 requires control thresholds to be set.
		 * - UART_MCR_RTS is ineffective if auto-RTS mode is enabled.
		 */
		if (termios->c_cflag & CRTSCTS)
			efr |= UART_EFR_CTS;

		serial_port_out(port, UART_LCR, UART_LCR_CONF_MODE_B);
		if (port->flags & UPF_EXAR_EFR)
			serial_port_out(port, UART_XR_EFR, efr);
		else
			serial_port_out(port, UART_EFR, efr);
	}

	serial8250_set_divisor(port, baud, quot, frac);

	/*
	 * LCR DLAB must be set to enable 64-byte FIFO mode. If the FCR
	 * is written without DLAB set, this mode will be disabled.
	 */
	if (port->type == PORT_16750)
		serial_port_out(port, UART_FCR, up->fcr);

	serial_port_out(port, UART_LCR, up->lcr);	/* reset DLAB */
	if (port->type != PORT_16750) {
		/* emulated UARTs (Lucent Venus 167x) need two steps */
		if (up->fcr & UART_FCR_ENABLE_FIFO)
			serial_port_out(port, UART_FCR, UART_FCR_ENABLE_FIFO);
		serial_port_out(port, UART_FCR, up->fcr);	/* set fcr */
	}
	serial8250_set_mctrl(port, port->mctrl);
	spin_unlock_irqrestore(&port->lock, flags);
	serial8250_rpm_put(up);

	/* Don't rewrite B0 */
	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);
}