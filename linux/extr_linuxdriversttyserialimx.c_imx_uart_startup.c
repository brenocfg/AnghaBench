#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct imx_port {TYPE_1__ port; scalar_t__ dte_mode; scalar_t__ have_rtscts; int /*<<< orphan*/  dma_is_enabled; int /*<<< orphan*/  clk_per; int /*<<< orphan*/  clk_ipg; } ;

/* Variables and functions */
 int CTSTL ; 
 int /*<<< orphan*/  RXTL_DEFAULT ; 
 int /*<<< orphan*/  TXTL_DEFAULT ; 
 int /*<<< orphan*/  UCR1 ; 
 int UCR1_RRDYEN ; 
 int UCR1_RTSDEN ; 
 int UCR1_UARTEN ; 
 int /*<<< orphan*/  UCR2 ; 
 int UCR2_ATEN ; 
 int UCR2_IRTS ; 
 int UCR2_RTSEN ; 
 int UCR2_RXEN ; 
 int UCR2_SRST ; 
 int UCR2_TXEN ; 
 int /*<<< orphan*/  UCR3 ; 
 int UCR3_DCD ; 
 int UCR3_DTRDEN ; 
 int UCR3_RI ; 
 int /*<<< orphan*/  UCR4 ; 
 int UCR4_CTSTL_MASK ; 
 int UCR4_CTSTL_SHF ; 
 int UCR4_DREN ; 
 int UCR4_OREN ; 
 int /*<<< orphan*/  USR1 ; 
 int USR1_DTRD ; 
 int USR1_RTSD ; 
 int /*<<< orphan*/  USR2 ; 
 int USR2_ORE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ imx_uart_dma_init (struct imx_port*) ; 
 int /*<<< orphan*/  imx_uart_enable_dma (struct imx_port*) ; 
 int /*<<< orphan*/  imx_uart_enable_ms (TYPE_1__*) ; 
 int /*<<< orphan*/  imx_uart_is_imx1 (struct imx_port*) ; 
 int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_setup_ufcr (struct imx_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_uart_start_rx_dma (struct imx_port*) ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uart_console (struct uart_port*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int imx_uart_startup(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	int retval, i;
	unsigned long flags;
	int dma_is_inited = 0;
	u32 ucr1, ucr2, ucr4;

	retval = clk_prepare_enable(sport->clk_per);
	if (retval)
		return retval;
	retval = clk_prepare_enable(sport->clk_ipg);
	if (retval) {
		clk_disable_unprepare(sport->clk_per);
		return retval;
	}

	imx_uart_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);

	/* disable the DREN bit (Data Ready interrupt enable) before
	 * requesting IRQs
	 */
	ucr4 = imx_uart_readl(sport, UCR4);

	/* set the trigger level for CTS */
	ucr4 &= ~(UCR4_CTSTL_MASK << UCR4_CTSTL_SHF);
	ucr4 |= CTSTL << UCR4_CTSTL_SHF;

	imx_uart_writel(sport, ucr4 & ~UCR4_DREN, UCR4);

	/* Can we enable the DMA support? */
	if (!uart_console(port) && imx_uart_dma_init(sport) == 0)
		dma_is_inited = 1;

	spin_lock_irqsave(&sport->port.lock, flags);
	/* Reset fifo's and state machines */
	i = 100;

	ucr2 = imx_uart_readl(sport, UCR2);
	ucr2 &= ~UCR2_SRST;
	imx_uart_writel(sport, ucr2, UCR2);

	while (!(imx_uart_readl(sport, UCR2) & UCR2_SRST) && (--i > 0))
		udelay(1);

	/*
	 * Finally, clear and enable interrupts
	 */
	imx_uart_writel(sport, USR1_RTSD | USR1_DTRD, USR1);
	imx_uart_writel(sport, USR2_ORE, USR2);

	ucr1 = imx_uart_readl(sport, UCR1) & ~UCR1_RRDYEN;
	ucr1 |= UCR1_UARTEN;
	if (sport->have_rtscts)
		ucr1 |= UCR1_RTSDEN;

	imx_uart_writel(sport, ucr1, UCR1);

	ucr4 = imx_uart_readl(sport, UCR4) & ~UCR4_OREN;
	if (!sport->dma_is_enabled)
		ucr4 |= UCR4_OREN;
	imx_uart_writel(sport, ucr4, UCR4);

	ucr2 = imx_uart_readl(sport, UCR2) & ~UCR2_ATEN;
	ucr2 |= (UCR2_RXEN | UCR2_TXEN);
	if (!sport->have_rtscts)
		ucr2 |= UCR2_IRTS;
	/*
	 * make sure the edge sensitive RTS-irq is disabled,
	 * we're using RTSD instead.
	 */
	if (!imx_uart_is_imx1(sport))
		ucr2 &= ~UCR2_RTSEN;
	imx_uart_writel(sport, ucr2, UCR2);

	if (!imx_uart_is_imx1(sport)) {
		u32 ucr3;

		ucr3 = imx_uart_readl(sport, UCR3);

		ucr3 |= UCR3_DTRDEN | UCR3_RI | UCR3_DCD;

		if (sport->dte_mode)
			/* disable broken interrupts */
			ucr3 &= ~(UCR3_RI | UCR3_DCD);

		imx_uart_writel(sport, ucr3, UCR3);
	}

	/*
	 * Enable modem status interrupts
	 */
	imx_uart_enable_ms(&sport->port);

	if (dma_is_inited) {
		imx_uart_enable_dma(sport);
		imx_uart_start_rx_dma(sport);
	} else {
		ucr1 = imx_uart_readl(sport, UCR1);
		ucr1 |= UCR1_RRDYEN;
		imx_uart_writel(sport, ucr1, UCR1);

		ucr2 = imx_uart_readl(sport, UCR2);
		ucr2 |= UCR2_ATEN;
		imx_uart_writel(sport, ucr2, UCR2);
	}

	spin_unlock_irqrestore(&sport->port.lock, flags);

	return 0;
}