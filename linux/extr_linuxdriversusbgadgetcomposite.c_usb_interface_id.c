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
struct usb_function {int dummy; } ;
struct usb_configuration {unsigned int next_interface_id; struct usb_function** interface; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int MAX_CONFIG_INTERFACES ; 

int usb_interface_id(struct usb_configuration *config,
		struct usb_function *function)
{
	unsigned id = config->next_interface_id;

	if (id < MAX_CONFIG_INTERFACES) {
		config->interface[id] = function;
		config->next_interface_id = id + 1;
		return id;
	}
	return -ENODEV;
}