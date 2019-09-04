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
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct ark3116_private {int mcr; int msr; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  hw_lock; } ;
typedef  int __u32 ;

/* Variables and functions */
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_OUT1 ; 
 int TIOCM_OUT2 ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT1 ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int UART_MSR_CTS ; 
 int UART_MSR_DCD ; 
 int UART_MSR_DSR ; 
 int UART_MSR_RI ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ark3116_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int ark3116_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ark3116_private *priv = usb_get_serial_port_data(port);
	__u32 status;
	__u32 ctrl;
	unsigned long flags;

	mutex_lock(&priv->hw_lock);
	ctrl = priv->mcr;
	mutex_unlock(&priv->hw_lock);

	spin_lock_irqsave(&priv->status_lock, flags);
	status = priv->msr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	return  (status & UART_MSR_DSR  ? TIOCM_DSR  : 0) |
		(status & UART_MSR_CTS  ? TIOCM_CTS  : 0) |
		(status & UART_MSR_RI   ? TIOCM_RI   : 0) |
		(status & UART_MSR_DCD  ? TIOCM_CD   : 0) |
		(ctrl   & UART_MCR_DTR  ? TIOCM_DTR  : 0) |
		(ctrl   & UART_MCR_RTS  ? TIOCM_RTS  : 0) |
		(ctrl   & UART_MCR_OUT1 ? TIOCM_OUT1 : 0) |
		(ctrl   & UART_MCR_OUT2 ? TIOCM_OUT2 : 0);
}