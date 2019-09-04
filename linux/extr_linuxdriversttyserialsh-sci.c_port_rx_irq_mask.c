#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {unsigned long scscr; } ;

/* Variables and functions */
 unsigned long SCSCR_REIE ; 
 unsigned long SCSCR_RIE ; 
 TYPE_2__* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static inline unsigned long port_rx_irq_mask(struct uart_port *port)
{
	/*
	 * Not all ports (such as SCIFA) will support REIE. Rather than
	 * special-casing the port type, we check the port initialization
	 * IRQ enable mask to see whether the IRQ is desired at all. If
	 * it's unset, it's logically inferred that there's no point in
	 * testing for it.
	 */
	return SCSCR_RIE | (to_sci_port(port)->cfg->scscr & SCSCR_REIE);
}