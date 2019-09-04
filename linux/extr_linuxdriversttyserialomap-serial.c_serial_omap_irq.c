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
struct TYPE_4__ {TYPE_1__* state; int /*<<< orphan*/  lock; } ;
struct uart_omap_port {int /*<<< orphan*/  port_activity; int /*<<< orphan*/  dev; TYPE_2__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  UART_IIR ; 
#define  UART_IIR_CTS_RTS_DSR 134 
#define  UART_IIR_MSI 133 
 unsigned int UART_IIR_NO_INT ; 
#define  UART_IIR_RDI 132 
#define  UART_IIR_RLSI 131 
#define  UART_IIR_RX_TIMEOUT 130 
#define  UART_IIR_THRI 129 
#define  UART_IIR_XOFF 128 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  check_modem_status (struct uart_omap_port*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 unsigned int serial_in (struct uart_omap_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_omap_rdi (struct uart_omap_port*,unsigned int) ; 
 int /*<<< orphan*/  serial_omap_rlsi (struct uart_omap_port*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_omap_port*,unsigned int) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t serial_omap_irq(int irq, void *dev_id)
{
	struct uart_omap_port *up = dev_id;
	unsigned int iir, lsr;
	unsigned int type;
	irqreturn_t ret = IRQ_NONE;
	int max_count = 256;

	spin_lock(&up->port.lock);
	pm_runtime_get_sync(up->dev);

	do {
		iir = serial_in(up, UART_IIR);
		if (iir & UART_IIR_NO_INT)
			break;

		ret = IRQ_HANDLED;
		lsr = serial_in(up, UART_LSR);

		/* extract IRQ type from IIR register */
		type = iir & 0x3e;

		switch (type) {
		case UART_IIR_MSI:
			check_modem_status(up);
			break;
		case UART_IIR_THRI:
			transmit_chars(up, lsr);
			break;
		case UART_IIR_RX_TIMEOUT:
			/* FALLTHROUGH */
		case UART_IIR_RDI:
			serial_omap_rdi(up, lsr);
			break;
		case UART_IIR_RLSI:
			serial_omap_rlsi(up, lsr);
			break;
		case UART_IIR_CTS_RTS_DSR:
			/* simply try again */
			break;
		case UART_IIR_XOFF:
			/* FALLTHROUGH */
		default:
			break;
		}
	} while (max_count--);

	spin_unlock(&up->port.lock);

	tty_flip_buffer_push(&up->port.state->port);

	pm_runtime_mark_last_busy(up->dev);
	pm_runtime_put_autosuspend(up->dev);
	up->port_activity = jiffies;

	return ret;
}