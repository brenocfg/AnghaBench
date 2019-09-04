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

/* Variables and functions */
 int /*<<< orphan*/  RP2_TXRX_CTL ; 
 int RP2_TXRX_CTL_DTR_m ; 
 int RP2_TXRX_CTL_LOOP_m ; 
 int RP2_TXRX_CTL_RTS_m ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  rp2_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rp2_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	rp2_rmw(port_to_up(port), RP2_TXRX_CTL,
		RP2_TXRX_CTL_DTR_m | RP2_TXRX_CTL_RTS_m | RP2_TXRX_CTL_LOOP_m,
		((mctrl & TIOCM_DTR) ? RP2_TXRX_CTL_DTR_m : 0) |
		((mctrl & TIOCM_RTS) ? RP2_TXRX_CTL_RTS_m : 0) |
		((mctrl & TIOCM_LOOP) ? RP2_TXRX_CTL_LOOP_m : 0));
}