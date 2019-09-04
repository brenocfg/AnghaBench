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
struct pic32_sport {int /*<<< orphan*/  hw_flow_ctrl; } ;

/* Variables and functions */
 unsigned int TIOCM_CD ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 scalar_t__ get_cts_state (struct pic32_sport*) ; 
 struct pic32_sport* to_pic32_sport (struct uart_port*) ; 

__attribute__((used)) static unsigned int pic32_uart_get_mctrl(struct uart_port *port)
{
	struct pic32_sport *sport = to_pic32_sport(port);
	unsigned int mctrl = 0;

	if (!sport->hw_flow_ctrl)
		mctrl |= TIOCM_CTS;
	else if (get_cts_state(sport))
		mctrl |= TIOCM_CTS;

	/* DSR and CD are not supported in PIC32, so return 1
	 * RI is not supported in PIC32, so return 0
	 */
	mctrl |= TIOCM_CD;
	mctrl |= TIOCM_DSR;

	return mctrl;
}