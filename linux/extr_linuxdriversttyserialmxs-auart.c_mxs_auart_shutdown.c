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
struct uart_port {int dummy; } ;
struct mxs_auart_port {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUART_CTRL0_CLKGATE ; 
 int AUART_CTRL2_UARTEN ; 
 int AUART_INTR_CTSMIEN ; 
 int AUART_INTR_RTIEN ; 
 int AUART_INTR_RXIEN ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  REG_CTRL2 ; 
 int /*<<< orphan*/  REG_INTR ; 
 scalar_t__ auart_dma_enabled (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_auart_disable_ms (struct uart_port*) ; 
 int /*<<< orphan*/  mxs_auart_dma_exit (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_auart_reset_assert (struct mxs_auart_port*) ; 
 int /*<<< orphan*/  mxs_clr (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_set (int /*<<< orphan*/ ,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 struct mxs_auart_port* to_auart_port (struct uart_port*) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

__attribute__((used)) static void mxs_auart_shutdown(struct uart_port *u)
{
	struct mxs_auart_port *s = to_auart_port(u);

	mxs_auart_disable_ms(u);

	if (auart_dma_enabled(s))
		mxs_auart_dma_exit(s);

	if (uart_console(u)) {
		mxs_clr(AUART_CTRL2_UARTEN, s, REG_CTRL2);

		mxs_clr(AUART_INTR_RXIEN | AUART_INTR_RTIEN |
			AUART_INTR_CTSMIEN, s, REG_INTR);
		mxs_set(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	} else {
		mxs_auart_reset_assert(s);
	}

	clk_disable_unprepare(s->clk);
}