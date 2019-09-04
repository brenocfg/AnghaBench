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
struct TYPE_3__ {int flags; scalar_t__ delay_rts_after_send; } ;
struct uart_port {TYPE_1__ rs485; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_status_mask; } ;
struct uart_omap_port {int scr; int ier; int fcr; int /*<<< orphan*/  dev; TYPE_2__ port; int /*<<< orphan*/  rts_gpio; } ;

/* Variables and functions */
 int OMAP_UART_SCR_TX_EMPTY ; 
 int SER_RS485_ENABLED ; 
 int SER_RS485_RTS_AFTER_SEND ; 
 int SER_RS485_RX_DURING_TX ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_THRI ; 
 int /*<<< orphan*/  UART_LSR_DR ; 
 int /*<<< orphan*/  UART_OMAP_SCR ; 
 int gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_omap_port*,int /*<<< orphan*/ ,int) ; 
 struct uart_omap_port* to_uart_omap_port (struct uart_port*) ; 

__attribute__((used)) static void serial_omap_stop_tx(struct uart_port *port)
{
	struct uart_omap_port *up = to_uart_omap_port(port);
	int res;

	pm_runtime_get_sync(up->dev);

	/* Handle RS-485 */
	if (port->rs485.flags & SER_RS485_ENABLED) {
		if (up->scr & OMAP_UART_SCR_TX_EMPTY) {
			/* THR interrupt is fired when both TX FIFO and TX
			 * shift register are empty. This means there's nothing
			 * left to transmit now, so make sure the THR interrupt
			 * is fired when TX FIFO is below the trigger level,
			 * disable THR interrupts and toggle the RS-485 GPIO
			 * data direction pin if needed.
			 */
			up->scr &= ~OMAP_UART_SCR_TX_EMPTY;
			serial_out(up, UART_OMAP_SCR, up->scr);
			res = (port->rs485.flags & SER_RS485_RTS_AFTER_SEND) ?
				1 : 0;
			if (gpio_get_value(up->rts_gpio) != res) {
				if (port->rs485.delay_rts_after_send > 0)
					mdelay(
					port->rs485.delay_rts_after_send);
				gpio_set_value(up->rts_gpio, res);
			}
		} else {
			/* We're asked to stop, but there's still stuff in the
			 * UART FIFO, so make sure the THR interrupt is fired
			 * when both TX FIFO and TX shift register are empty.
			 * The next THR interrupt (if no transmission is started
			 * in the meantime) will indicate the end of a
			 * transmission. Therefore we _don't_ disable THR
			 * interrupts in this situation.
			 */
			up->scr |= OMAP_UART_SCR_TX_EMPTY;
			serial_out(up, UART_OMAP_SCR, up->scr);
			return;
		}
	}

	if (up->ier & UART_IER_THRI) {
		up->ier &= ~UART_IER_THRI;
		serial_out(up, UART_IER, up->ier);
	}

	if ((port->rs485.flags & SER_RS485_ENABLED) &&
	    !(port->rs485.flags & SER_RS485_RX_DURING_TX)) {
		/*
		 * Empty the RX FIFO, we are not interested in anything
		 * received during the half-duplex transmission.
		 */
		serial_out(up, UART_FCR, up->fcr | UART_FCR_CLEAR_RCVR);
		/* Re-enable RX interrupts */
		up->ier |= UART_IER_RLSI | UART_IER_RDI;
		up->port.read_status_mask |= UART_LSR_DR;
		serial_out(up, UART_IER, up->ier);
	}

	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
}