#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long uint64_t ;
typedef  unsigned long u32 ;
struct TYPE_4__ {int flags; } ;
struct uart_port {int uartclk; TYPE_1__ rs485; } ;
struct ktermios {unsigned int c_cflag; int c_iflag; } ;
struct TYPE_5__ {int read_status_mask; int ignore_status_mask; unsigned int uartclk; int /*<<< orphan*/  lock; } ;
struct imx_port {TYPE_2__ port; int /*<<< orphan*/  timer; scalar_t__ have_rtscts; } ;
typedef  int /*<<< orphan*/  speed_t ;

/* Variables and functions */
 int BRKINT ; 
 int CREAD ; 
 int CRTSCTS ; 
 unsigned int CS7 ; 
 unsigned int CS8 ; 
 unsigned int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int /*<<< orphan*/  IMX21_ONEMS ; 
 int INPCK ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 scalar_t__ UART_ENABLE_MS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 unsigned long UCR1_RRDYEN ; 
 unsigned long UCR1_RTSDEN ; 
 unsigned long UCR1_TXMPTYEN ; 
 int /*<<< orphan*/  UCR2 ; 
 unsigned long UCR2_ATEN ; 
 unsigned long UCR2_IRTS ; 
 unsigned long UCR2_PREN ; 
 unsigned long UCR2_PROE ; 
 unsigned long UCR2_RXEN ; 
 unsigned long UCR2_SRST ; 
 unsigned long UCR2_STPB ; 
 unsigned long UCR2_TXEN ; 
 unsigned long UCR2_WS ; 
 int /*<<< orphan*/  UFCR ; 
 unsigned long UFCR_RFDIV ; 
 unsigned long UFCR_RFDIV_REG (unsigned long) ; 
 int URXD_BRK ; 
 int URXD_DUMMY_READ ; 
 int URXD_FRMERR ; 
 int URXD_OVRRUN ; 
 int URXD_PRERR ; 
 int /*<<< orphan*/  USR2 ; 
 unsigned long USR2_TXDC ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  imx_uart_enable_ms (TYPE_2__*) ; 
 int /*<<< orphan*/  imx_uart_is_imx1 (struct imx_port*) ; 
 unsigned long imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_rts_active (struct imx_port*,unsigned long*) ; 
 int /*<<< orphan*/  imx_uart_rts_auto (struct imx_port*,unsigned long*) ; 
 int /*<<< orphan*/  imx_uart_rts_inactive (struct imx_port*,unsigned long*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rational_best_approximation (int,unsigned int,int,int,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_termios_encode_baud_rate (struct ktermios*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int,int) ; 
 unsigned int uart_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
imx_uart_set_termios(struct uart_port *port, struct ktermios *termios,
		     struct ktermios *old)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long flags;
	u32 ucr2, old_ucr1, old_ucr2, ufcr;
	unsigned int baud, quot;
	unsigned int old_csize = old ? old->c_cflag & CSIZE : CS8;
	unsigned long div;
	unsigned long num, denom;
	uint64_t tdiv64;

	/*
	 * We only support CS7 and CS8.
	 */
	while ((termios->c_cflag & CSIZE) != CS7 &&
	       (termios->c_cflag & CSIZE) != CS8) {
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= old_csize;
		old_csize = CS8;
	}

	if ((termios->c_cflag & CSIZE) == CS8)
		ucr2 = UCR2_WS | UCR2_SRST | UCR2_IRTS;
	else
		ucr2 = UCR2_SRST | UCR2_IRTS;

	if (termios->c_cflag & CRTSCTS) {
		if (sport->have_rtscts) {
			ucr2 &= ~UCR2_IRTS;

			if (port->rs485.flags & SER_RS485_ENABLED) {
				/*
				 * RTS is mandatory for rs485 operation, so keep
				 * it under manual control and keep transmitter
				 * disabled.
				 */
				if (port->rs485.flags &
				    SER_RS485_RTS_AFTER_SEND)
					imx_uart_rts_active(sport, &ucr2);
				else
					imx_uart_rts_inactive(sport, &ucr2);
			} else {
				imx_uart_rts_auto(sport, &ucr2);
			}
		} else {
			termios->c_cflag &= ~CRTSCTS;
		}
	} else if (port->rs485.flags & SER_RS485_ENABLED) {
		/* disable transmitter */
		if (port->rs485.flags & SER_RS485_RTS_AFTER_SEND)
			imx_uart_rts_active(sport, &ucr2);
		else
			imx_uart_rts_inactive(sport, &ucr2);
	}


	if (termios->c_cflag & CSTOPB)
		ucr2 |= UCR2_STPB;
	if (termios->c_cflag & PARENB) {
		ucr2 |= UCR2_PREN;
		if (termios->c_cflag & PARODD)
			ucr2 |= UCR2_PROE;
	}

	del_timer_sync(&sport->timer);

	/*
	 * Ask the core to calculate the divisor for us.
	 */
	baud = uart_get_baud_rate(port, termios, old, 50, port->uartclk / 16);
	quot = uart_get_divisor(port, baud);

	spin_lock_irqsave(&sport->port.lock, flags);

	sport->port.read_status_mask = 0;
	if (termios->c_iflag & INPCK)
		sport->port.read_status_mask |= (URXD_FRMERR | URXD_PRERR);
	if (termios->c_iflag & (BRKINT | PARMRK))
		sport->port.read_status_mask |= URXD_BRK;

	/*
	 * Characters to ignore
	 */
	sport->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		sport->port.ignore_status_mask |= URXD_PRERR | URXD_FRMERR;
	if (termios->c_iflag & IGNBRK) {
		sport->port.ignore_status_mask |= URXD_BRK;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			sport->port.ignore_status_mask |= URXD_OVRRUN;
	}

	if ((termios->c_cflag & CREAD) == 0)
		sport->port.ignore_status_mask |= URXD_DUMMY_READ;

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	/*
	 * disable interrupts and drain transmitter
	 */
	old_ucr1 = imx_uart_readl(sport, UCR1);
	imx_uart_writel(sport,
			old_ucr1 & ~(UCR1_TXMPTYEN | UCR1_RRDYEN | UCR1_RTSDEN),
			UCR1);
	old_ucr2 = imx_uart_readl(sport, UCR2);
	imx_uart_writel(sport, old_ucr2 & ~UCR2_ATEN, UCR2);

	while (!(imx_uart_readl(sport, USR2) & USR2_TXDC))
		barrier();

	/* then, disable everything */
	imx_uart_writel(sport, old_ucr2 & ~(UCR2_TXEN | UCR2_RXEN | UCR2_ATEN), UCR2);
	old_ucr2 &= (UCR2_TXEN | UCR2_RXEN | UCR2_ATEN);

	/* custom-baudrate handling */
	div = sport->port.uartclk / (baud * 16);
	if (baud == 38400 && quot != div)
		baud = sport->port.uartclk / (quot * 16);

	div = sport->port.uartclk / (baud * 16);
	if (div > 7)
		div = 7;
	if (!div)
		div = 1;

	rational_best_approximation(16 * div * baud, sport->port.uartclk,
		1 << 16, 1 << 16, &num, &denom);

	tdiv64 = sport->port.uartclk;
	tdiv64 *= num;
	do_div(tdiv64, denom * 16 * div);
	tty_termios_encode_baud_rate(termios,
				(speed_t)tdiv64, (speed_t)tdiv64);

	num -= 1;
	denom -= 1;

	ufcr = imx_uart_readl(sport, UFCR);
	ufcr = (ufcr & (~UFCR_RFDIV)) | UFCR_RFDIV_REG(div);
	imx_uart_writel(sport, ufcr, UFCR);

	imx_uart_writel(sport, num, UBIR);
	imx_uart_writel(sport, denom, UBMR);

	if (!imx_uart_is_imx1(sport))
		imx_uart_writel(sport, sport->port.uartclk / div / 1000,
				IMX21_ONEMS);

	imx_uart_writel(sport, old_ucr1, UCR1);

	/* set the parity, stop bits and data size */
	imx_uart_writel(sport, ucr2 | old_ucr2, UCR2);

	if (UART_ENABLE_MS(&sport->port, termios->c_cflag))
		imx_uart_enable_ms(&sport->port);

	spin_unlock_irqrestore(&sport->port.lock, flags);
}