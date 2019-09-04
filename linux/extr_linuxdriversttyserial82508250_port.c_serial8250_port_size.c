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
struct TYPE_2__ {unsigned int mapsize; scalar_t__ iotype; scalar_t__ type; int regshift; } ;
struct uart_8250_port {TYPE_1__ port; } ;

/* Variables and functions */
 scalar_t__ PORT_RT2880 ; 
 scalar_t__ UPIO_AU ; 
 scalar_t__ is_omap1_8250 (struct uart_8250_port*) ; 

__attribute__((used)) static unsigned int serial8250_port_size(struct uart_8250_port *pt)
{
	if (pt->port.mapsize)
		return pt->port.mapsize;
	if (pt->port.iotype == UPIO_AU) {
		if (pt->port.type == PORT_RT2880)
			return 0x100;
		return 0x1000;
	}
	if (is_omap1_8250(pt))
		return 0x16 << pt->port.regshift;

	return 8 << pt->port.regshift;
}