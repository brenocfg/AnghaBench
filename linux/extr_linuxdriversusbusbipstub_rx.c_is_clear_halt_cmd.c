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
struct usb_ctrlrequest {scalar_t__ bRequest; scalar_t__ bRequestType; scalar_t__ wValue; } ;
struct urb {scalar_t__ setup_packet; } ;

/* Variables and functions */
 scalar_t__ USB_ENDPOINT_HALT ; 
 scalar_t__ USB_RECIP_ENDPOINT ; 
 scalar_t__ USB_REQ_CLEAR_FEATURE ; 

__attribute__((used)) static int is_clear_halt_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;

	req = (struct usb_ctrlrequest *) urb->setup_packet;

	 return (req->bRequest == USB_REQ_CLEAR_FEATURE) &&
		 (req->bRequestType == USB_RECIP_ENDPOINT) &&
		 (req->wValue == USB_ENDPOINT_HALT);
}