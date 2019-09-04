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

/* Variables and functions */
 int /*<<< orphan*/  CP210X_IFC_ENABLE ; 
 int /*<<< orphan*/  CP210X_PURGE ; 
 int /*<<< orphan*/  PURGE_ALL ; 
 int /*<<< orphan*/  UART_DISABLE ; 
 int /*<<< orphan*/  cp210x_write_u16_reg (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 

__attribute__((used)) static void cp210x_close(struct usb_serial_port *port)
{
	usb_serial_generic_close(port);

	/* Clear both queues; cp2108 needs this to avoid an occasional hang */
	cp210x_write_u16_reg(port, CP210X_PURGE, PURGE_ALL);

	cp210x_write_u16_reg(port, CP210X_IFC_ENABLE, UART_DISABLE);
}