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
struct uart_port {scalar_t__ type; } ;
struct sci_port {unsigned int hscif_tot; int rx_trigger; int /*<<< orphan*/  rx_fifo_timer; scalar_t__ rx_fifo_timeout; } ;
struct plat_sci_reg {scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 int /*<<< orphan*/  SCFCR ; 
 unsigned int SCFCR_RFRST ; 
 unsigned int SCFCR_TFRST ; 
 int /*<<< orphan*/  SCLSR ; 
 unsigned int SCLSR_ORER ; 
 unsigned int SCLSR_TO ; 
 int /*<<< orphan*/  SCSCR ; 
 int SCxSR_BREAK_CLEAR (struct uart_port*) ; 
 int SCxSR_ERROR_CLEAR (struct uart_port*) ; 
 int SCxSR_RDxF_CLEAR (struct uart_port*) ; 
 int /*<<< orphan*/  rx_fifo_timer_fn ; 
 int /*<<< orphan*/  sci_clear_SCxSR (struct uart_port*,int) ; 
 struct plat_sci_reg* sci_getreg (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_set_rtrg (struct uart_port*,int) ; 
 unsigned int serial_port_in (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_port_out (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static void sci_reset(struct uart_port *port)
{
	const struct plat_sci_reg *reg;
	unsigned int status;
	struct sci_port *s = to_sci_port(port);

	serial_port_out(port, SCSCR, s->hscif_tot);	/* TE=0, RE=0, CKE1=0 */

	reg = sci_getreg(port, SCFCR);
	if (reg->size)
		serial_port_out(port, SCFCR, SCFCR_RFRST | SCFCR_TFRST);

	sci_clear_SCxSR(port,
			SCxSR_RDxF_CLEAR(port) & SCxSR_ERROR_CLEAR(port) &
			SCxSR_BREAK_CLEAR(port));
	if (sci_getreg(port, SCLSR)->size) {
		status = serial_port_in(port, SCLSR);
		status &= ~(SCLSR_TO | SCLSR_ORER);
		serial_port_out(port, SCLSR, status);
	}

	if (s->rx_trigger > 1) {
		if (s->rx_fifo_timeout) {
			scif_set_rtrg(port, 1);
			timer_setup(&s->rx_fifo_timer, rx_fifo_timer_fn, 0);
		} else {
			if (port->type == PORT_SCIFA ||
			    port->type == PORT_SCIFB)
				scif_set_rtrg(port, 1);
			else
				scif_set_rtrg(port, s->rx_trigger);
		}
	}
}