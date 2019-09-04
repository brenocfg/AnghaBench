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
struct uart_port {int uartclk; int /*<<< orphan*/  ignore_status_mask; int /*<<< orphan*/  read_status_mask; } ;
struct mxs_auart_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct ktermios {unsigned int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int AUART_CTRL2_CTSEN ; 
 int AUART_CTRL2_DMAONERR ; 
 int AUART_CTRL2_RTSEN ; 
 int AUART_CTRL2_RXDMAE ; 
 int AUART_CTRL2_RXE ; 
 int AUART_CTRL2_TXDMAE ; 
 int AUART_INTR_RTIEN ; 
 int AUART_INTR_RXIEN ; 
 int AUART_LINECTRL_BAUD_DIVFRAC (int) ; 
 int AUART_LINECTRL_BAUD_DIVINT (int) ; 
 int /*<<< orphan*/  AUART_LINECTRL_BAUD_DIV_MAX ; 
 int AUART_LINECTRL_BAUD_DIV_MIN ; 
 int AUART_LINECTRL_EPS ; 
 int AUART_LINECTRL_FEN ; 
 int AUART_LINECTRL_PEN ; 
 int AUART_LINECTRL_SPS ; 
 int AUART_LINECTRL_STP2 ; 
 int AUART_LINECTRL_WLEN (int) ; 
 int /*<<< orphan*/  AUART_STAT_BERR ; 
 int /*<<< orphan*/  AUART_STAT_OERR ; 
 int /*<<< orphan*/  AUART_STAT_PERR ; 
 int BRKINT ; 
 unsigned int CMSPAR ; 
 unsigned int CREAD ; 
 unsigned int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 scalar_t__ CTS_AT_AUART () ; 
 int DIV_ROUND_CLOSEST (int,unsigned int) ; 
 unsigned int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int /*<<< orphan*/  MXS_AUART_DMA_RX_READY ; 
 int /*<<< orphan*/  MXS_AUART_RTSCTS ; 
 unsigned int PARENB ; 
 int PARMRK ; 
 unsigned int PARODD ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 int /*<<< orphan*/  REG_INTR ; 
 int /*<<< orphan*/  REG_LINECTRL ; 
 scalar_t__ UART_ENABLE_MS (struct uart_port*,unsigned int) ; 
 scalar_t__ auart_dma_enabled (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_asm9260_auart (struct mxs_auart_port*) ; 
 scalar_t__ is_imx28_auart (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  mxs_auart_dma_exit (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_dma_init (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_dma_prep_rx (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_enable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  mxs_clr (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_write (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,unsigned int,unsigned int) ; 

__attribute__((used)) static void mxs_auart_settermios(struct uart_port *u,
				 struct ktermios *termios,
				 struct ktermios *old)
{
	struct mxs_auart_port *s = to_auart_port(u);
	u32 bm, ctrl, ctrl2, div;
	unsigned int cflag, baud, baud_min, baud_max;

	cflag = termios->c_cflag;

	ctrl = AUART_LINECTRL_FEN;
	ctrl2 = mxs_read(s, REG_CTRL2);

	/* byte size */
	switch (cflag & CSIZE) {
	case CS5:
		bm = 0;
		break;
	case CS6:
		bm = 1;
		break;
	case CS7:
		bm = 2;
		break;
	case CS8:
		bm = 3;
		break;
	default:
		return;
	}

	ctrl |= AUART_LINECTRL_WLEN(bm);

	/* parity */
	if (cflag & PARENB) {
		ctrl |= AUART_LINECTRL_PEN;
		if ((cflag & PARODD) == 0)
			ctrl |= AUART_LINECTRL_EPS;
		if (cflag & CMSPAR)
			ctrl |= AUART_LINECTRL_SPS;
	}

	u->read_status_mask = AUART_STAT_OERR;

	if (termios->c_iflag & INPCK)
		u->read_status_mask |= AUART_STAT_PERR;
	if (termios->c_iflag & (IGNBRK | BRKINT | PARMRK))
		u->read_status_mask |= AUART_STAT_BERR;

	/*
	 * Characters to ignore
	 */
	u->ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		u->ignore_status_mask |= AUART_STAT_PERR;
	if (termios->c_iflag & IGNBRK) {
		u->ignore_status_mask |= AUART_STAT_BERR;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			u->ignore_status_mask |= AUART_STAT_OERR;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if (cflag & CREAD)
		ctrl2 |= AUART_CTRL2_RXE;
	else
		ctrl2 &= ~AUART_CTRL2_RXE;

	/* figure out the stop bits requested */
	if (cflag & CSTOPB)
		ctrl |= AUART_LINECTRL_STP2;

	/* figure out the hardware flow control settings */
	ctrl2 &= ~(AUART_CTRL2_CTSEN | AUART_CTRL2_RTSEN);
	if (cflag & CRTSCTS) {
		/*
		 * The DMA has a bug(see errata:2836) in mx23.
		 * So we can not implement the DMA for auart in mx23,
		 * we can only implement the DMA support for auart
		 * in mx28.
		 */
		if (is_imx28_auart(s)
				&& test_bit(MXS_AUART_RTSCTS, &s->flags)) {
			if (!mxs_auart_dma_init(s))
				/* enable DMA tranfer */
				ctrl2 |= AUART_CTRL2_TXDMAE | AUART_CTRL2_RXDMAE
				       | AUART_CTRL2_DMAONERR;
		}
		/* Even if RTS is GPIO line RTSEN can be enabled because
		 * the pinctrl configuration decides about RTS pin function */
		ctrl2 |= AUART_CTRL2_RTSEN;
		if (CTS_AT_AUART())
			ctrl2 |= AUART_CTRL2_CTSEN;
	}

	/* set baud rate */
	if (is_asm9260_auart(s)) {
		baud = uart_get_baud_rate(u, termios, old,
					  u->uartclk * 4 / 0x3FFFFF,
					  u->uartclk / 16);
		div = u->uartclk * 4 / baud;
	} else {
		baud_min = DIV_ROUND_UP(u->uartclk * 32,
					AUART_LINECTRL_BAUD_DIV_MAX);
		baud_max = u->uartclk * 32 / AUART_LINECTRL_BAUD_DIV_MIN;
		baud = uart_get_baud_rate(u, termios, old, baud_min, baud_max);
		div = DIV_ROUND_CLOSEST(u->uartclk * 32, baud);
	}

	ctrl |= AUART_LINECTRL_BAUD_DIVFRAC(div & 0x3F);
	ctrl |= AUART_LINECTRL_BAUD_DIVINT(div >> 6);
	mxs_write(ctrl, s, REG_LINECTRL);

	mxs_write(ctrl2, s, REG_CTRL2);

	uart_update_timeout(u, termios->c_cflag, baud);

	/* prepare for the DMA RX. */
	if (auart_dma_enabled(s) &&
		!test_and_set_bit(MXS_AUART_DMA_RX_READY, &s->flags)) {
		if (!mxs_auart_dma_prep_rx(s)) {
			/* Disable the normal RX interrupt. */
			mxs_clr(AUART_INTR_RXIEN | AUART_INTR_RTIEN,
				s, REG_INTR);
		} else {
			mxs_auart_dma_exit(s);
			dev_err(s->dev, "We can not start up the DMA.\n");
		}
	}

	/* CTS flow-control and modem-status interrupts */
	if (UART_ENABLE_MS(u, termios->c_cflag))
		mxs_auart_enable_ms(u);
	else
		mxs_auart_disable_ms(u);
}