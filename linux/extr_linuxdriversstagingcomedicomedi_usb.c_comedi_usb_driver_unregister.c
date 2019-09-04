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
struct usb_driver {int dummy; } ;
struct comedi_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  comedi_driver_unregister (struct comedi_driver*) ; 
 int /*<<< orphan*/  usb_deregister (struct usb_driver*) ; 

void comedi_usb_driver_unregister(struct comedi_driver *comedi_driver,
				  struct usb_driver *usb_driver)
{
	usb_deregister(usb_driver);
	comedi_driver_unregister(comedi_driver);
}