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
struct usb_ctrlrequest {int dummy; } ;
struct urb {struct usb_ctrlrequest* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_ctrlrequest*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void ap_urb_complete(struct urb *urb)
{
	struct usb_ctrlrequest *dr = urb->context;

	kfree(dr);
	usb_free_urb(urb);
}