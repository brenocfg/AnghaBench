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
struct imx_port {int context_saved; int* saved_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX21_UTS ; 
 int /*<<< orphan*/  UBIR ; 
 int /*<<< orphan*/  UBMR ; 
 int /*<<< orphan*/  UCR1 ; 
 int /*<<< orphan*/  UCR2 ; 
 int UCR2_SRST ; 
 int /*<<< orphan*/  UCR3 ; 
 int /*<<< orphan*/  UCR4 ; 
 int /*<<< orphan*/  UESC ; 
 int /*<<< orphan*/  UFCR ; 
 int /*<<< orphan*/  UTIM ; 
 int /*<<< orphan*/  imx_uart_writel (struct imx_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_uart_restore_context(struct imx_port *sport)
{
	if (!sport->context_saved)
		return;

	imx_uart_writel(sport, sport->saved_reg[4], UFCR);
	imx_uart_writel(sport, sport->saved_reg[5], UESC);
	imx_uart_writel(sport, sport->saved_reg[6], UTIM);
	imx_uart_writel(sport, sport->saved_reg[7], UBIR);
	imx_uart_writel(sport, sport->saved_reg[8], UBMR);
	imx_uart_writel(sport, sport->saved_reg[9], IMX21_UTS);
	imx_uart_writel(sport, sport->saved_reg[0], UCR1);
	imx_uart_writel(sport, sport->saved_reg[1] | UCR2_SRST, UCR2);
	imx_uart_writel(sport, sport->saved_reg[2], UCR3);
	imx_uart_writel(sport, sport->saved_reg[3], UCR4);
	sport->context_saved = false;
}