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
struct usb_request {int /*<<< orphan*/  length; int /*<<< orphan*/  dma; scalar_t__ buf; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_ep_free_buffer (struct usb_ep*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,struct usb_request*) ; 

__attribute__((used)) static void free_ep_req (struct usb_ep *ep, struct usb_request *req)
{
	if (req->buf)
		usb_ep_free_buffer (ep, req->buf, req->dma, req->length);
	usb_ep_free_request (ep, req);
}