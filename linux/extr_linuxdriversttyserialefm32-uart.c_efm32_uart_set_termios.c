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
typedef  int u32 ;
struct uart_port {int uartclk; int read_status_mask; int ignore_status_mask; int /*<<< orphan*/  lock; } ;
struct ktermios {int c_cflag; int c_iflag; } ;
struct efm32_uart_port {int dummy; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int DIV_ROUND_CLOSEST (int,int) ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int SW_UARTn_RXDATAX_BERR ; 
 int /*<<< orphan*/  UARTn_CLKDIV ; 
 int /*<<< orphan*/  UARTn_CMD ; 
 int UARTn_CMD_RXDIS ; 
 int UARTn_CMD_RXEN ; 
 int UARTn_CMD_TXDIS ; 
 int UARTn_CMD_TXEN ; 
 int /*<<< orphan*/  UARTn_CTRL ; 
 int UARTn_CTRL_TXBIL ; 
 int /*<<< orphan*/  UARTn_FRAME ; 
 int UARTn_FRAME_DATABITS (int) ; 
 int UARTn_FRAME_PARITY_EVEN ; 
 int UARTn_FRAME_PARITY_NONE ; 
 int UARTn_FRAME_PARITY_ODD ; 
 int UARTn_FRAME_STOPBITS_ONE ; 
 int UARTn_FRAME_STOPBITS_TWO ; 
 int UARTn_RXDATAX_FERR ; 
 int UARTn_RXDATAX_PERR ; 
 int UARTn_RXDATAX_RXDATA__MASK ; 
 int /*<<< orphan*/  efm32_uart_write32 (struct efm32_uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct efm32_uart_port* to_efm_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void efm32_uart_set_termios(struct uart_port *port,
		struct ktermios *new, struct ktermios *old)
{
	struct efm32_uart_port *efm_port = to_efm_port(port);
	unsigned long flags;
	unsigned baud;
	u32 clkdiv;
	u32 frame = 0;

	/* no modem control lines */
	new->c_cflag &= ~(CRTSCTS | CMSPAR);

	baud = uart_get_baud_rate(port, new, old,
			DIV_ROUND_CLOSEST(port->uartclk, 16 * 8192),
			DIV_ROUND_CLOSEST(port->uartclk, 16));

	switch (new->c_cflag & CSIZE) {
	case CS5:
		frame |= UARTn_FRAME_DATABITS(5);
		break;
	case CS6:
		frame |= UARTn_FRAME_DATABITS(6);
		break;
	case CS7:
		frame |= UARTn_FRAME_DATABITS(7);
		break;
	case CS8:
		frame |= UARTn_FRAME_DATABITS(8);
		break;
	}

	if (new->c_cflag & CSTOPB)
		/* the receiver only verifies the first stop bit */
		frame |= UARTn_FRAME_STOPBITS_TWO;
	else
		frame |= UARTn_FRAME_STOPBITS_ONE;

	if (new->c_cflag & PARENB) {
		if (new->c_cflag & PARODD)
			frame |= UARTn_FRAME_PARITY_ODD;
		else
			frame |= UARTn_FRAME_PARITY_EVEN;
	} else
		frame |= UARTn_FRAME_PARITY_NONE;

	/*
	 * the 6 lowest bits of CLKDIV are dc, bit 6 has value 0.25.
	 * port->uartclk <= 14e6, so 4 * port->uartclk doesn't overflow.
	 */
	clkdiv = (DIV_ROUND_CLOSEST(4 * port->uartclk, 16 * baud) - 4) << 6;

	spin_lock_irqsave(&port->lock, flags);

	efm32_uart_write32(efm_port,
			UARTn_CMD_TXDIS | UARTn_CMD_RXDIS, UARTn_CMD);

	port->read_status_mask = UARTn_RXDATAX_RXDATA__MASK;
	if (new->c_iflag & INPCK)
		port->read_status_mask |=
			UARTn_RXDATAX_FERR | UARTn_RXDATAX_PERR;
	if (new->c_iflag & (IGNBRK | BRKINT | PARMRK))
		port->read_status_mask |= SW_UARTn_RXDATAX_BERR;

	port->ignore_status_mask = 0;
	if (new->c_iflag & IGNPAR)
		port->ignore_status_mask |=
			UARTn_RXDATAX_FERR | UARTn_RXDATAX_PERR;
	if (new->c_iflag & IGNBRK)
		port->ignore_status_mask |= SW_UARTn_RXDATAX_BERR;

	uart_update_timeout(port, new->c_cflag, baud);

	efm32_uart_write32(efm_port, UARTn_CTRL_TXBIL, UARTn_CTRL);
	efm32_uart_write32(efm_port, frame, UARTn_FRAME);
	efm32_uart_write32(efm_port, clkdiv, UARTn_CLKDIV);

	efm32_uart_write32(efm_port, UARTn_CMD_TXEN | UARTn_CMD_RXEN,
			UARTn_CMD);

	spin_unlock_irqrestore(&port->lock, flags);
}