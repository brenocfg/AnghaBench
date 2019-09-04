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
struct uart_port {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__* params; } ;
struct TYPE_3__ {scalar_t__ overrun_mask; } ;

/* Variables and functions */
 scalar_t__ PORT_SCI ; 
 scalar_t__ SCIFA_ORER ; 
 unsigned int SCIF_FERC ; 
 unsigned int SCIF_PERC ; 
 int /*<<< orphan*/  SCxSR ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_clear_SCxSR(struct uart_port *port, unsigned int mask)
{
	if (port->type == PORT_SCI) {
		/* Just store the mask */
		serial_port_out(port, SCxSR, mask);
	} else if (to_sci_port(port)->params->overrun_mask == SCIFA_ORER) {
		/* SCIFA/SCIFB and SCIF on SH7705/SH7720/SH7721 */
		/* Only clear the status bits we want to clear */
		serial_port_out(port, SCxSR,
				serial_port_in(port, SCxSR) & mask);
	} else {
		/* Store the mask, clear parity/framing errors */
		serial_port_out(port, SCxSR, mask & ~(SCIF_FERC | SCIF_PERC));
	}
}