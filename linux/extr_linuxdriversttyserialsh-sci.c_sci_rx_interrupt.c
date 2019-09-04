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
struct sci_port {int rx_trigger; int rx_fifo_timeout; int rx_frame; int /*<<< orphan*/  rx_fifo_timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int) ; 
 int HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sci_receive_chars (void*) ; 
 int /*<<< orphan*/  scif_rtrg_enabled (struct uart_port*) ; 
 int /*<<< orphan*/  scif_set_rtrg (struct uart_port*,int) ; 
 struct sci_port* to_sci_port (struct uart_port*) ; 

__attribute__((used)) static irqreturn_t sci_rx_interrupt(int irq, void *ptr)
{
	struct uart_port *port = ptr;
	struct sci_port *s = to_sci_port(port);

#ifdef CONFIG_SERIAL_SH_SCI_DMA
	if (s->chan_rx) {
		u16 scr = serial_port_in(port, SCSCR);
		u16 ssr = serial_port_in(port, SCxSR);

		/* Disable future Rx interrupts */
		if (port->type == PORT_SCIFA || port->type == PORT_SCIFB) {
			disable_irq_nosync(irq);
			scr |= SCSCR_RDRQE;
		} else {
			if (sci_submit_rx(s, false) < 0)
				goto handle_pio;

			scr &= ~SCSCR_RIE;
		}
		serial_port_out(port, SCSCR, scr);
		/* Clear current interrupt */
		serial_port_out(port, SCxSR,
				ssr & ~(SCIF_DR | SCxSR_RDxF(port)));
		dev_dbg(port->dev, "Rx IRQ %lu: setup t-out in %u us\n",
			jiffies, s->rx_timeout);
		start_hrtimer_us(&s->rx_timer, s->rx_timeout);

		return IRQ_HANDLED;
	}

handle_pio:
#endif

	if (s->rx_trigger > 1 && s->rx_fifo_timeout > 0) {
		if (!scif_rtrg_enabled(port))
			scif_set_rtrg(port, s->rx_trigger);

		mod_timer(&s->rx_fifo_timer, jiffies + DIV_ROUND_UP(
			  s->rx_frame * HZ * s->rx_fifo_timeout, 1000000));
	}

	/* I think sci_receive_chars has to be called irrespective
	 * of whether the I_IXOFF is set, otherwise, how is the interrupt
	 * to be disabled?
	 */
	sci_receive_chars(ptr);

	return IRQ_HANDLED;
}