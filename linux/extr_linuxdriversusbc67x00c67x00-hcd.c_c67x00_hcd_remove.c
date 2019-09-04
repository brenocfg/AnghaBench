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
struct usb_hcd {int dummy; } ;
struct c67x00_sie {struct c67x00_hcd* private_data; } ;
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
 struct usb_hcd* c67x00_hcd_to_hcd (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_sched_stop_scheduler (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

void c67x00_hcd_remove(struct c67x00_sie *sie)
{
	struct c67x00_hcd *c67x00 = sie->private_data;
	struct usb_hcd *hcd = c67x00_hcd_to_hcd(c67x00);

	c67x00_sched_stop_scheduler(c67x00);
	usb_remove_hcd(hcd);
	usb_put_hcd(hcd);
}