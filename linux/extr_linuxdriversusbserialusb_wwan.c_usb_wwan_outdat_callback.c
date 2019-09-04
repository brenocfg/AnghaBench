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
struct usb_wwan_port_private {int /*<<< orphan*/  out_busy; struct urb** out_urbs; } ;
struct usb_wwan_intf_private {int /*<<< orphan*/  susp_lock; int /*<<< orphan*/  in_flight; } ;
struct usb_serial_port {TYPE_1__* serial; } ;
struct urb {struct usb_serial_port* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int N_OUT_URB ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_autopm_put_interface_async (int /*<<< orphan*/ ) ; 
 struct usb_wwan_intf_private* usb_get_serial_data (TYPE_1__*) ; 
 struct usb_wwan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_serial_port_softint (struct usb_serial_port*) ; 

__attribute__((used)) static void usb_wwan_outdat_callback(struct urb *urb)
{
	struct usb_serial_port *port;
	struct usb_wwan_port_private *portdata;
	struct usb_wwan_intf_private *intfdata;
	unsigned long flags;
	int i;

	port = urb->context;
	intfdata = usb_get_serial_data(port->serial);

	usb_serial_port_softint(port);
	usb_autopm_put_interface_async(port->serial->interface);
	portdata = usb_get_serial_port_data(port);
	spin_lock_irqsave(&intfdata->susp_lock, flags);
	intfdata->in_flight--;
	spin_unlock_irqrestore(&intfdata->susp_lock, flags);

	for (i = 0; i < N_OUT_URB; ++i) {
		if (portdata->out_urbs[i] == urb) {
			smp_mb__before_atomic();
			clear_bit(i, &portdata->out_busy);
			break;
		}
	}
}