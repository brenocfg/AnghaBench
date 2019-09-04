#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int uartclk; } ;
struct TYPE_3__ {unsigned int fifosize; int read_status_mask; int ignore_status_mask; int status; int flags; int /*<<< orphan*/  line; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;
struct uart_omap_port {unsigned int calc_latency; unsigned int latency; unsigned int dll; unsigned int dlh; unsigned char mdr1; int fcr; unsigned char ier; unsigned char lcr; unsigned char scr; unsigned char efr; unsigned char mcr; int errata; TYPE_1__ port; int /*<<< orphan*/  dev; int /*<<< orphan*/  qos_work; } ;
struct ktermios {int c_cflag; int c_iflag; unsigned char* c_cc; } ;

/* Variables and functions */
 int BRKINT ; 
 int CMSPAR ; 
 int CREAD ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int OMAP_UART_FCR_RX_FIFO_TRIG_MASK ; 
 int OMAP_UART_FCR_TX_FIFO_TRIG_MASK ; 
 unsigned char OMAP_UART_SCR_RX_TRIG_GRANU1_MASK ; 
 int OMAP_UART_SW_CLR ; 
 int OMAP_UART_SW_RX ; 
 int OMAP_UART_SW_TX ; 
 unsigned char OMAP_UART_TCR_TRIG ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  UART_EFR ; 
 int UART_EFR_CTS ; 
 unsigned char UART_EFR_ECB ; 
 int UART_EFR_RTS ; 
 unsigned char UART_EFR_SCD ; 
 scalar_t__ UART_ENABLE_MS (TYPE_1__*,int) ; 
 int UART_ERRATA_i202_MDR1_ACCESS ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR6_R_TRIGGER_16 ; 
 int UART_FCR6_T_TRIGGER_24 ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_FCR_R_TRIG_01 ; 
 int UART_FCR_T_TRIG_01 ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned char UART_IER_MSI ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned char UART_LCR_CONF_MODE_A ; 
 unsigned char UART_LCR_CONF_MODE_B ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_SPAR ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN5 ; 
 unsigned char UART_LCR_WLEN6 ; 
 unsigned char UART_LCR_WLEN7 ; 
 unsigned char UART_LCR_WLEN8 ; 
 int UART_LSR_BI ; 
 int UART_LSR_DR ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_MCR ; 
 unsigned char UART_MCR_TCRTLR ; 
 unsigned char UART_MCR_XONANY ; 
 int /*<<< orphan*/  UART_OMAP_MDR1 ; 
 unsigned char UART_OMAP_MDR1_13X_MODE ; 
 unsigned char UART_OMAP_MDR1_16X_MODE ; 
 unsigned char UART_OMAP_MDR1_DISABLE ; 
 int /*<<< orphan*/  UART_OMAP_SCR ; 
 int /*<<< orphan*/  UART_TI752_TCR ; 
 int /*<<< orphan*/  UART_XOFF1 ; 
 int /*<<< orphan*/  UART_XON1 ; 
 int UPF_HARD_FLOW ; 
 int UPF_SOFT_FLOW ; 
 int UPSTAT_AUTOCTS ; 
 int UPSTAT_AUTORTS ; 
 int UPSTAT_AUTOXOFF ; 
 unsigned int USEC_PER_SEC ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 unsigned char serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_baud_is_mode16 (struct uart_port*,unsigned int) ; 
 unsigned int serial_omap_get_divisor (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  serial_omap_mdr1_errataset (struct uart_omap_port*,unsigned char) ; 
 int /*<<< orphan*/  serial_omap_set_mctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 
 unsigned int uart_get_baud_rate (struct uart_port*,struct ktermios*,struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_update_timeout (struct uart_port*,int,unsigned int) ; 

__attribute__((used)) static void
serial_omap_set_termios(struct uart_port *port, struct ktermios *termios,
			struct ktermios *old)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	unsigned char cval = 0;
	unsigned long flags = 0;
	unsigned int baud, quot;

	switch (termios->c_cflag & CSIZE) {
	case CS5:
		cval = UART_LCR_WLEN5;
		break;
	case CS6:
		cval = UART_LCR_WLEN6;
		break;
	case CS7:
		cval = UART_LCR_WLEN7;
		break;
	default:
	case CS8:
		cval = UART_LCR_WLEN8;
		break;
	}

	if (termios->c_cflag & CSTOPB)
		cval |= UART_LCR_STOP;
	if (termios->c_cflag & PARENB)
		cval |= UART_LCR_PARITY;
	if (!(termios->c_cflag & PARODD))
		cval |= UART_LCR_EPAR;
	if (termios->c_cflag & CMSPAR)
		cval |= UART_LCR_SPAR;

	/*
	 * Ask the core to calculate the divisor for us.
	 */

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/13);
	quot = serial_omap_get_divisor(port, baud);

	/* calculate wakeup latency constraint */
	up->calc_latency = (USEC_PER_SEC * up->port.fifosize) / (baud / 8);
	up->latency = up->calc_latency;
	schedule_work(&up->qos_work);

	up->dll = quot & 0xff;
	up->dlh = quot >> 8;
	up->mdr1 = UART_OMAP_MDR1_DISABLE;

	up->fcr = UART_FCR_R_TRIG_01 | UART_FCR_T_TRIG_01 |
			UART_FCR_ENABLE_FIFO;

	/*
	 * Ok, we're now changing the port state. Do it with
	 * interrupts disabled.
	 */
	pm_runtime_get_sync(up->dev);
	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Update the per-port timeout.
	 */
	uart_update_timeout(port, termios->c_cflag, baud);

	up->port.read_status_mask = UART_LSR_OE | UART_LSR_THRE | UART_LSR_DR;
	if (termios->c_iflag & INPCK)
		up->port.read_status_mask |= UART_LSR_FE | UART_LSR_PE;
	if (termios->c_iflag & (BRKINT | PARMRK))
		up->port.read_status_mask |= UART_LSR_BI;

	/*
	 * Characters to ignore
	 */
	up->port.ignore_status_mask = 0;
	if (termios->c_iflag & IGNPAR)
		up->port.ignore_status_mask |= UART_LSR_PE | UART_LSR_FE;
	if (termios->c_iflag & IGNBRK) {
		up->port.ignore_status_mask |= UART_LSR_BI;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too (for real raw support).
		 */
		if (termios->c_iflag & IGNPAR)
			up->port.ignore_status_mask |= UART_LSR_OE;
	}

	/*
	 * ignore all characters if CREAD is not set
	 */
	if ((termios->c_cflag & CREAD) == 0)
		up->port.ignore_status_mask |= UART_LSR_DR;

	/*
	 * Modem status interrupts
	 */
	up->ier &= ~UART_IER_MSI;
	if (UART_ENABLE_MS(&up->port, termios->c_cflag))
		up->ier |= UART_IER_MSI;
	serial_out(up, UART_IER, up->ier);
	serial_out(up, UART_LCR, cval);		/* reset DLAB */
	up->lcr = cval;
	up->scr = 0;

	/* FIFOs and DMA Settings */

	/* FCR can be changed only when the
	 * baud clock is not running
	 * DLL_REG and DLH_REG set to 0.
	 */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_DLL, 0);
	serial_out(up, UART_DLM, 0);
	serial_out(up, UART_LCR, 0);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	up->efr = serial_in(up, UART_EFR) & ~UART_EFR_ECB;
	up->efr &= ~UART_EFR_SCD;
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	up->mcr = serial_in(up, UART_MCR) & ~UART_MCR_TCRTLR;
	serial_out(up, UART_MCR, up->mcr | UART_MCR_TCRTLR);
	/* FIFO ENABLE, DMA MODE */

	up->scr |= OMAP_UART_SCR_RX_TRIG_GRANU1_MASK;
	/*
	 * NOTE: Setting OMAP_UART_SCR_RX_TRIG_GRANU1_MASK
	 * sets Enables the granularity of 1 for TRIGGER RX
	 * level. Along with setting RX FIFO trigger level
	 * to 1 (as noted below, 16 characters) and TLR[3:0]
	 * to zero this will result RX FIFO threshold level
	 * to 1 character, instead of 16 as noted in comment
	 * below.
	 */

	/* Set receive FIFO threshold to 16 characters and
	 * transmit FIFO threshold to 32 spaces
	 */
	up->fcr &= ~OMAP_UART_FCR_RX_FIFO_TRIG_MASK;
	up->fcr &= ~OMAP_UART_FCR_TX_FIFO_TRIG_MASK;
	up->fcr |= UART_FCR6_R_TRIGGER_16 | UART_FCR6_T_TRIGGER_24 |
		UART_FCR_ENABLE_FIFO;

	serial_out(up, UART_FCR, up->fcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_OMAP_SCR, up->scr);

	/* Reset UART_MCR_TCRTLR: this must be done with the EFR_ECB bit set */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_MCR, up->mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);

	/* Protocol, Baud Rate, and Interrupt Settings */

	if (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, up->mdr1);
	else
		serial_out(up, UART_OMAP_MDR1, up->mdr1);

	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);

	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_IER, 0);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_DLL, up->dll);	/* LS of divisor */
	serial_out(up, UART_DLM, up->dlh);	/* MS of divisor */

	serial_out(up, UART_LCR, 0);
	serial_out(up, UART_IER, up->ier);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, cval);

	if (!serial_omap_baud_is_mode16(port, baud))
		up->mdr1 = UART_OMAP_MDR1_13X_MODE;
	else
		up->mdr1 = UART_OMAP_MDR1_16X_MODE;

	if (up->errata & UART_ERRATA_i202_MDR1_ACCESS)
		serial_omap_mdr1_errataset(up, up->mdr1);
	else
		serial_out(up, UART_OMAP_MDR1, up->mdr1);

	/* Configure flow control */
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);

	/* XON1/XOFF1 accessible mode B, TCRTLR=0, ECB=0 */
	serial_out(up, UART_XON1, termios->c_cc[VSTART]);
	serial_out(up, UART_XOFF1, termios->c_cc[VSTOP]);

	/* Enable access to TCR/TLR */
	serial_out(up, UART_EFR, up->efr | UART_EFR_ECB);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_A);
	serial_out(up, UART_MCR, up->mcr | UART_MCR_TCRTLR);

	serial_out(up, UART_TI752_TCR, OMAP_UART_TCR_TRIG);

	up->port.status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	if (termios->c_cflag & CRTSCTS && up->port.flags & UPF_HARD_FLOW) {
		/* Enable AUTOCTS (autoRTS is enabled when RTS is raised) */
		up->port.status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		up->efr |= UART_EFR_CTS;
	} else {
		/* Disable AUTORTS and AUTOCTS */
		up->efr &= ~(UART_EFR_CTS | UART_EFR_RTS);
	}

	if (up->port.flags & UPF_SOFT_FLOW) {
		/* clear SW control mode bits */
		up->efr &= OMAP_UART_SW_CLR;

		/*
		 * IXON Flag:
		 * Enable XON/XOFF flow control on input.
		 * Receiver compares XON1, XOFF1.
		 */
		if (termios->c_iflag & IXON)
			up->efr |= OMAP_UART_SW_RX;

		/*
		 * IXOFF Flag:
		 * Enable XON/XOFF flow control on output.
		 * Transmit XON1, XOFF1
		 */
		if (termios->c_iflag & IXOFF) {
			up->port.status |= UPSTAT_AUTOXOFF;
			up->efr |= OMAP_UART_SW_TX;
		}

		/*
		 * IXANY Flag:
		 * Enable any character to restart output.
		 * Operation resumes after receiving any
		 * character after recognition of the XOFF character
		 */
		if (termios->c_iflag & IXANY)
			up->mcr |= UART_MCR_XONANY;
		else
			up->mcr &= ~UART_MCR_XONANY;
	}
	serial_out(up, UART_MCR, up->mcr);
	serial_out(up, UART_LCR, UART_LCR_CONF_MODE_B);
	serial_out(up, UART_EFR, up->efr);
	serial_out(up, UART_LCR, up->lcr);

	serial_omap_set_mctrl(&up->port, up->port.mctrl);

	spin_unlock_irqrestore(&up->port.lock, flags);
	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
	dev_dbg(up->port.dev, "serial_omap_set_termios+%d\n", up->port.line);
}