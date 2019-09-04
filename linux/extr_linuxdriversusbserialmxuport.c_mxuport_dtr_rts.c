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
typedef  int u8 ;
struct usb_serial_port {int dummy; } ;
struct mxuport_port {int mcr_state; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxuport_set_mcr (struct usb_serial_port*,int) ; 
 struct mxuport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void mxuport_dtr_rts(struct usb_serial_port *port, int on)
{
	struct mxuport_port *mxport = usb_get_serial_port_data(port);
	u8 mcr_state;
	int err;

	mutex_lock(&mxport->mutex);
	mcr_state = mxport->mcr_state;

	if (on)
		mcr_state |= (UART_MCR_RTS | UART_MCR_DTR);
	else
		mcr_state &= ~(UART_MCR_RTS | UART_MCR_DTR);

	err = mxuport_set_mcr(port, mcr_state);
	if (!err)
		mxport->mcr_state = mcr_state;

	mutex_unlock(&mxport->mutex);
}