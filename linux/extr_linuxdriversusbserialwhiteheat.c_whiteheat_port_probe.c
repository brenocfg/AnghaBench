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
struct whiteheat_private {int dummy; } ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct whiteheat_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,struct whiteheat_private*) ; 

__attribute__((used)) static int whiteheat_port_probe(struct usb_serial_port *port)
{
	struct whiteheat_private *info;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	usb_set_serial_port_data(port, info);

	return 0;
}