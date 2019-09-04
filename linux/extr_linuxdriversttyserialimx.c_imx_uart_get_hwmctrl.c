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
struct imx_port {scalar_t__ dte_mode; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RI ; 
 int /*<<< orphan*/  USR1 ; 
 unsigned int USR1_RTSS ; 
 int /*<<< orphan*/  USR2 ; 
 unsigned int USR2_DCDIN ; 
 unsigned int USR2_RIIN ; 
 unsigned int imx_uart_readl (struct imx_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int imx_uart_get_hwmctrl(struct imx_port *sport)
{
	unsigned int tmp = TIOCM_DSR;
	unsigned usr1 = imx_uart_readl(sport, USR1);
	unsigned usr2 = imx_uart_readl(sport, USR2);

	if (usr1 & USR1_RTSS)
		tmp |= TIOCM_CTS;

	/* in DCE mode DCDIN is always 0 */
	if (!(usr2 & USR2_DCDIN))
		tmp |= TIOCM_CAR;

	if (sport->dte_mode)
		if (!(imx_uart_readl(sport, USR2) & USR2_RIIN))
			tmp |= TIOCM_RI;

	return tmp;
}