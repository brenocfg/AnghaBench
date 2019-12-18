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
struct usb_line6_variax {int dummy; } ;
struct usb_interface {int dummy; } ;
struct usb_device_id {size_t driver_info; } ;

/* Variables and functions */
 int line6_probe (struct usb_interface*,struct usb_device_id const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  variax_init ; 
 int /*<<< orphan*/ * variax_properties_table ; 

__attribute__((used)) static int variax_probe(struct usb_interface *interface,
			const struct usb_device_id *id)
{
	return line6_probe(interface, id, "Line6-Variax",
			   &variax_properties_table[id->driver_info],
			   variax_init, sizeof(struct usb_line6_variax));
}