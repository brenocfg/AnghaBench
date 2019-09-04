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
typedef  unsigned int u32 ;
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  uartclk; } ;
struct mvebu_uart {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned int BRDV_BAUD_MASK ; 
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ UART_BRDV ; 
 unsigned int readl (scalar_t__) ; 
 struct mvebu_uart* to_mvuart (struct uart_port*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int mvebu_uart_baud_rate_set(struct uart_port *port, unsigned int baud)
{
	struct mvebu_uart *mvuart = to_mvuart(port);
	unsigned int baud_rate_div;
	u32 brdv;

	if (IS_ERR(mvuart->clk))
		return -PTR_ERR(mvuart->clk);

	/*
	 * The UART clock is divided by the value of the divisor to generate
	 * UCLK_OUT clock, which is 16 times faster than the baudrate.
	 * This prescaler can achieve all standard baudrates until 230400.
	 * Higher baudrates could be achieved for the extended UART by using the
	 * programmable oversampling stack (also called fractional divisor).
	 */
	baud_rate_div = DIV_ROUND_UP(port->uartclk, baud * 16);
	brdv = readl(port->membase + UART_BRDV);
	brdv &= ~BRDV_BAUD_MASK;
	brdv |= baud_rate_div;
	writel(brdv, port->membase + UART_BRDV);

	return 0;
}