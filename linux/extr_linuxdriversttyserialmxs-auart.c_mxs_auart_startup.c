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
struct uart_port {int /*<<< orphan*/  fifosize; } ;
struct mxs_auart_port {int ms_irq_enabled; int /*<<< orphan*/  mctrl_prev; int /*<<< orphan*/  gpios; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUART_CTRL0_CLKGATE ; 
 int /*<<< orphan*/  AUART_CTRL2_UARTEN ; 
 int AUART_INTR_CTSMIEN ; 
 int AUART_INTR_RTIEN ; 
 int AUART_INTR_RXIEN ; 
 int /*<<< orphan*/  AUART_LINECTRL_FEN ; 
 int /*<<< orphan*/  MXS_AUART_FIFO_SIZE ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 int /*<<< orphan*/  REG_INTR ; 
 int /*<<< orphan*/  REG_LINECTRL ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mctrl_gpio_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxs_auart_reset_assert (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_reset_deassert (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_clr (int /*<<< orphan*/ ,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_set (int /*<<< orphan*/ ,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_write (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

__attribute__((used)) static int mxs_auart_startup(struct uart_port *u)
{
	int ret;
	struct mxs_auart_port *s = to_auart_port(u);

	ret = clk_prepare_enable(s->clk);
	if (ret)
		return ret;

	if (uart_console(u)) {
		mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	} else {
		/* reset the unit to a well known state */
		mxs_auart_reset_assert(s);
		mxs_auart_reset_deassert(s);
	}

	mxs_set(AUART_CTRL2_UARTEN, s, REG_CTRL2);

	mxs_write(AUART_INTR_RXIEN | AUART_INTR_RTIEN | AUART_INTR_CTSMIEN,
		  s, REG_INTR);

	/* Reset FIFO size (it could have changed if DMA was enabled) */
	u->fifosize = MXS_AUART_FIFO_SIZE;

	/*
	 * Enable fifo so all four bytes of a DMA word are written to
	 * output (otherwise, only the LSB is written, ie. 1 in 4 bytes)
	 */
	mxs_set(AUART_LINECTRL_FEN, s, REG_LINECTRL);

	/* get initial status of modem lines */
	mctrl_gpio_get(s->gpios, &s->mctrl_prev);

	s->ms_irq_enabled = false;
	return 0;
}