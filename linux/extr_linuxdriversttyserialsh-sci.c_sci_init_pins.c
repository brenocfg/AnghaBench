#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct uart_port {scalar_t__ type; int mctrl; } ;
struct sci_port {int /*<<< orphan*/  autorts; scalar_t__ has_rtscts; TYPE_2__* cfg; } ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_pins ) (struct uart_port*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCPCR ; 
 int SCPCR_CTSC ; 
 int SCPCR_RTSC ; 
 int SCPCR_RXDC ; 
 int SCPCR_TXDC ; 
 int /*<<< orphan*/  SCPDR ; 
 int SCPDR_RTSD ; 
 int /*<<< orphan*/  SCSPTR ; 
 int SCSPTR_CTSIO ; 
 int SCSPTR_RTSDT ; 
 int SCSPTR_RTSIO ; 
 int SCSPTR_SCKIO ; 
 int TIOCM_RTS ; 
 TYPE_3__* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,unsigned int) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_init_pins(struct uart_port *port, unsigned int cflag)
{
	struct sci_port *s = to_sci_port(port);

	/*
	 * Use port-specific handler if provided.
	 */
	if (s->cfg->ops && s->cfg->ops->init_pins) {
		s->cfg->ops->init_pins(port, cflag);
		return;
	}

	if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
		u16 data = serial_port_in(port, SCPDR);
		u16 ctrl = serial_port_in(port, SCPCR);

		/* Enable RXD and TXD pin functions */
		ctrl &= ~(SCPCR_RXDC | SCPCR_TXDC);
		if (to_sci_port(port)->has_rtscts) {
			/* RTS# is output, active low, unless autorts */
			if (!(port->mctrl & TIOCM_RTS)) {
				ctrl |= SCPCR_RTSC;
				data |= SCPDR_RTSD;
			} else if (!s->autorts) {
				ctrl |= SCPCR_RTSC;
				data &= ~SCPDR_RTSD;
			} else {
				/* Enable RTS# pin function */
				ctrl &= ~SCPCR_RTSC;
			}
			/* Enable CTS# pin function */
			ctrl &= ~SCPCR_CTSC;
		}
		serial_port_out(port, SCPDR, data);
		serial_port_out(port, SCPCR, ctrl);
	} else if (sci_getreg(port, SCSPTR)->size) {
		u16 status = serial_port_in(port, SCSPTR);

		/* RTS# is always output; and active low, unless autorts */
		status |= SCSPTR_RTSIO;
		if (!(port->mctrl & TIOCM_RTS))
			status |= SCSPTR_RTSDT;
		else if (!s->autorts)
			status &= ~SCSPTR_RTSDT;
		/* CTS# and SCK are inputs */
		status &= ~(SCSPTR_CTSIO | SCSPTR_SCKIO);
		serial_port_out(port, SCSPTR, status);
	}
}