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
struct usb_request {size_t length; int /*<<< orphan*/  buf; } ;
struct usb_ep {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_dir_out (int /*<<< orphan*/ ) ; 
 size_t usb_ep_align (struct usb_ep*,size_t) ; 
 struct usb_request* usb_ep_alloc_request (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (struct usb_ep*,struct usb_request*) ; 

struct usb_request *alloc_ep_req(struct usb_ep *ep, size_t len)
{
	struct usb_request      *req;

	req = usb_ep_alloc_request(ep, GFP_ATOMIC);
	if (req) {
		req->length = usb_endpoint_dir_out(ep->desc) ?
			usb_ep_align(ep, len) : len;
		req->buf = kmalloc(req->length, GFP_ATOMIC);
		if (!req->buf) {
			usb_ep_free_request(ep, req);
			req = NULL;
		}
	}
	return req;
}