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
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; struct cdns_uart* private_data; } ;
struct cdns_uart {int quirks; } ;

/* Variables and functions */
 scalar_t__ CDNS_UART_CR ; 
 int CDNS_UART_CR_RXRST ; 
 unsigned int CDNS_UART_CR_RX_DIS ; 
 unsigned int CDNS_UART_CR_RX_EN ; 
 int CDNS_UART_CR_TXRST ; 
 unsigned int CDNS_UART_CR_TX_DIS ; 
 scalar_t__ CDNS_UART_IER ; 
 scalar_t__ CDNS_UART_ISR ; 
 unsigned int CDNS_UART_IXR_BRK ; 
 scalar_t__ CDNS_UART_MR ; 
 unsigned int CDNS_UART_MR_CHARLEN_8_BIT ; 
 unsigned int CDNS_UART_MR_CHMODE_NORM ; 
 unsigned int CDNS_UART_MR_PARITY_NONE ; 
 unsigned int CDNS_UART_MR_STOPMODE_1_BIT ; 
 int /*<<< orphan*/  CDNS_UART_NAME ; 
 int CDNS_UART_RXBS_SUPPORT ; 
 scalar_t__ CDNS_UART_RXTOUT ; 
 scalar_t__ CDNS_UART_RXWM ; 
 unsigned int CDNS_UART_RX_IRQS ; 
 int /*<<< orphan*/  cdns_uart_isr ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 unsigned int readl (scalar_t__) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_port*) ; 
 unsigned int rx_timeout ; 
 unsigned int rx_trigger_level ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int cdns_uart_startup(struct uart_port *port)
{
	struct cdns_uart *cdns_uart = port->private_data;
	bool is_brk_support;
	int ret;
	unsigned long flags;
	unsigned int status = 0;

	is_brk_support = cdns_uart->quirks & CDNS_UART_RXBS_SUPPORT;

	spin_lock_irqsave(&port->lock, flags);

	/* Disable the TX and RX */
	writel(CDNS_UART_CR_TX_DIS | CDNS_UART_CR_RX_DIS,
			port->membase + CDNS_UART_CR);

	/* Set the Control Register with TX/RX Enable, TX/RX Reset,
	 * no break chars.
	 */
	writel(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST,
			port->membase + CDNS_UART_CR);

	while (readl(port->membase + CDNS_UART_CR) &
		(CDNS_UART_CR_TXRST | CDNS_UART_CR_RXRST))
		cpu_relax();

	/*
	 * Clear the RX disable bit and then set the RX enable bit to enable
	 * the receiver.
	 */
	status = readl(port->membase + CDNS_UART_CR);
	status &= ~CDNS_UART_CR_RX_DIS;
	status |= CDNS_UART_CR_RX_EN;
	writel(status, port->membase + CDNS_UART_CR);

	/* Set the Mode Register with normal mode,8 data bits,1 stop bit,
	 * no parity.
	 */
	writel(CDNS_UART_MR_CHMODE_NORM | CDNS_UART_MR_STOPMODE_1_BIT
		| CDNS_UART_MR_PARITY_NONE | CDNS_UART_MR_CHARLEN_8_BIT,
		port->membase + CDNS_UART_MR);

	/*
	 * Set the RX FIFO Trigger level to use most of the FIFO, but it
	 * can be tuned with a module parameter
	 */
	writel(rx_trigger_level, port->membase + CDNS_UART_RXWM);

	/*
	 * Receive Timeout register is enabled but it
	 * can be tuned with a module parameter
	 */
	writel(rx_timeout, port->membase + CDNS_UART_RXTOUT);

	/* Clear out any pending interrupts before enabling them */
	writel(readl(port->membase + CDNS_UART_ISR),
			port->membase + CDNS_UART_ISR);

	spin_unlock_irqrestore(&port->lock, flags);

	ret = request_irq(port->irq, cdns_uart_isr, 0, CDNS_UART_NAME, port);
	if (ret) {
		dev_err(port->dev, "request_irq '%d' failed with %d\n",
			port->irq, ret);
		return ret;
	}

	/* Set the Interrupt Registers with desired interrupts */
	if (is_brk_support)
		writel(CDNS_UART_RX_IRQS | CDNS_UART_IXR_BRK,
					port->membase + CDNS_UART_IER);
	else
		writel(CDNS_UART_RX_IRQS, port->membase + CDNS_UART_IER);

	return 0;
}