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
struct zero_dev {int /*<<< orphan*/  resume; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct zero_dev*,char*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct zero_dev* get_gadget_data (struct usb_gadget*) ; 

__attribute__((used)) static void
zero_resume (struct usb_gadget *gadget)
{
	struct zero_dev		*dev = get_gadget_data (gadget);

	DBG (dev, "resume\n");
	del_timer (&dev->resume);
}