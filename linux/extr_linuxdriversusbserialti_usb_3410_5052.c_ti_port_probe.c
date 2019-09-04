#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int drain_delay; int /*<<< orphan*/  closing_wait; } ;
struct usb_serial_port {TYPE_1__ port; TYPE_3__* serial; } ;
struct ti_port {int /*<<< orphan*/  tp_uart_mode; TYPE_2__* tp_tdev; struct usb_serial_port* tp_port; int /*<<< orphan*/  tp_uart_base_addr; int /*<<< orphan*/  tp_lock; } ;
struct TYPE_6__ {struct usb_serial_port** port; } ;
struct TYPE_5__ {scalar_t__ td_rs485_only; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TI_UART1_BASE_ADDR ; 
 int /*<<< orphan*/  TI_UART2_BASE_ADDR ; 
 int /*<<< orphan*/  TI_UART_232 ; 
 int /*<<< orphan*/  TI_UART_485_RECEIVER_DISABLED ; 
 int closing_wait ; 
 struct ti_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* usb_get_serial_data (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct ti_port*) ; 

__attribute__((used)) static int ti_port_probe(struct usb_serial_port *port)
{
	struct ti_port *tport;

	tport = kzalloc(sizeof(*tport), GFP_KERNEL);
	if (!tport)
		return -ENOMEM;

	spin_lock_init(&tport->tp_lock);
	if (port == port->serial->port[0])
		tport->tp_uart_base_addr = TI_UART1_BASE_ADDR;
	else
		tport->tp_uart_base_addr = TI_UART2_BASE_ADDR;
	port->port.closing_wait = msecs_to_jiffies(10 * closing_wait);
	tport->tp_port = port;
	tport->tp_tdev = usb_get_serial_data(port->serial);

	if (tport->tp_tdev->td_rs485_only)
		tport->tp_uart_mode = TI_UART_485_RECEIVER_DISABLED;
	else
		tport->tp_uart_mode = TI_UART_232;

	usb_set_serial_port_data(port, tport);

	port->port.drain_delay = 3;

	return 0;
}