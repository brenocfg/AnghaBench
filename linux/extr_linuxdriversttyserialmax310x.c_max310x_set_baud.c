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
struct uart_port {unsigned int uartclk; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 unsigned int MAX310X_BRGCFG_2XMODE_BIT ; 
 unsigned int MAX310X_BRGCFG_4XMODE_BIT ; 
 int /*<<< orphan*/  MAX310X_BRGCFG_REG ; 
 int /*<<< orphan*/  MAX310X_BRGDIVLSB_REG ; 
 int /*<<< orphan*/  MAX310X_BRGDIVMSB_REG ; 
 int /*<<< orphan*/  max310x_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max310x_set_baud(struct uart_port *port, int baud)
{
	unsigned int mode = 0, clk = port->uartclk, div = clk / baud;

	/* Check for minimal value for divider */
	if (div < 16)
		div = 16;

	if (clk % baud && (div / 16) < 0x8000) {
		/* Mode x2 */
		mode = MAX310X_BRGCFG_2XMODE_BIT;
		clk = port->uartclk * 2;
		div = clk / baud;

		if (clk % baud && (div / 16) < 0x8000) {
			/* Mode x4 */
			mode = MAX310X_BRGCFG_4XMODE_BIT;
			clk = port->uartclk * 4;
			div = clk / baud;
		}
	}

	max310x_port_write(port, MAX310X_BRGDIVMSB_REG, (div / 16) >> 8);
	max310x_port_write(port, MAX310X_BRGDIVLSB_REG, div / 16);
	max310x_port_write(port, MAX310X_BRGCFG_REG, (div % 16) | mode);

	return DIV_ROUND_CLOSEST(clk, div);
}