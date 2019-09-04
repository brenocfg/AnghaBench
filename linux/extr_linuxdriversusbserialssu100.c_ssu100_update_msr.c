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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_3__ {int /*<<< orphan*/  rng; int /*<<< orphan*/  dcd; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct usb_serial_port {TYPE_2__ port; TYPE_1__ icount; } ;
struct ssu100_port_private {int shadowMSR; int /*<<< orphan*/  status_lock; } ;

/* Variables and functions */
 int UART_MSR_ANY_DELTA ; 
 int UART_MSR_DCTS ; 
 int UART_MSR_DDCD ; 
 int UART_MSR_DDSR ; 
 int UART_MSR_TERI ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ssu100_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ssu100_update_msr(struct usb_serial_port *port, u8 msr)
{
	struct ssu100_port_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shadowMSR = msr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	if (msr & UART_MSR_ANY_DELTA) {
		/* update input line counters */
		if (msr & UART_MSR_DCTS)
			port->icount.cts++;
		if (msr & UART_MSR_DDSR)
			port->icount.dsr++;
		if (msr & UART_MSR_DDCD)
			port->icount.dcd++;
		if (msr & UART_MSR_TERI)
			port->icount.rng++;
		wake_up_interruptible(&port->port.delta_msr_wait);
	}
}