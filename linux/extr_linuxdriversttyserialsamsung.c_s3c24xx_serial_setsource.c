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
struct s3c24xx_uart_info {int num_clks; unsigned int clksel_mask; unsigned int clksel_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct s3c24xx_uart_info* s3c24xx_port_to_info (struct uart_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void s3c24xx_serial_setsource(struct uart_port *port,
			unsigned int clk_sel)
{
	struct s3c24xx_uart_info *info = s3c24xx_port_to_info(port);
	unsigned int ucon;

	if (info->num_clks == 1)
		return;

	ucon = rd_regl(port, S3C2410_UCON);
	if ((ucon & info->clksel_mask) >> info->clksel_shift == clk_sel)
		return;

	ucon &= ~info->clksel_mask;
	ucon |= clk_sel << info->clksel_shift;
	wr_regl(port, S3C2410_UCON, ucon);
}