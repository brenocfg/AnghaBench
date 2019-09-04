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
struct moschip_port {unsigned int shadowMCR; unsigned int shadowMSR; } ;

/* Variables and functions */
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RI ; 
 unsigned int TIOCM_RTS ; 
 unsigned int UART_MCR_DTR ; 
 unsigned int UART_MCR_RTS ; 
 unsigned int UART_MSR_CTS ; 
 unsigned int UART_MSR_DCD ; 
 unsigned int UART_MSR_DSR ; 
 unsigned int UART_MSR_RI ; 
 struct moschip_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int mos7720_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct moschip_port *mos7720_port = usb_get_serial_port_data(port);
	unsigned int result = 0;
	unsigned int mcr ;
	unsigned int msr ;

	mcr = mos7720_port->shadowMCR;
	msr = mos7720_port->shadowMSR;

	result = ((mcr & UART_MCR_DTR)  ? TIOCM_DTR : 0)   /* 0x002 */
	  | ((mcr & UART_MCR_RTS)   ? TIOCM_RTS : 0)   /* 0x004 */
	  | ((msr & UART_MSR_CTS)   ? TIOCM_CTS : 0)   /* 0x020 */
	  | ((msr & UART_MSR_DCD)   ? TIOCM_CAR : 0)   /* 0x040 */
	  | ((msr & UART_MSR_RI)    ? TIOCM_RI :  0)   /* 0x080 */
	  | ((msr & UART_MSR_DSR)   ? TIOCM_DSR : 0);  /* 0x100 */

	return result;
}