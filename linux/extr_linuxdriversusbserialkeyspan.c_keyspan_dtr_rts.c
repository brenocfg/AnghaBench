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
struct usb_serial_port {int dummy; } ;
struct keyspan_port_private {int rts_state; int dtr_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspan_send_setup (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void keyspan_dtr_rts(struct usb_serial_port *port, int on)
{
	struct keyspan_port_private *p_priv = usb_get_serial_port_data(port);

	p_priv->rts_state = on;
	p_priv->dtr_state = on;
	keyspan_send_setup(port, 0);
}