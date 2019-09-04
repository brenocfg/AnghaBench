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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_rts ) (struct uart_port*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int TIOCM_RTS ; 
 TYPE_1__* psc_ops ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void
mpc52xx_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	psc_ops->set_rts(port, mctrl & TIOCM_RTS);
}