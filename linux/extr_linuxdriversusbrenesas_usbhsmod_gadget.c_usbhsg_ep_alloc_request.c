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
struct usb_request {int dummy; } ;
struct usbhsg_request {struct usb_request req; } ;
struct usb_ep {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct usbhsg_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhs_pkt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhsg_ureq_to_pkt (struct usbhsg_request*) ; 

__attribute__((used)) static struct usb_request *usbhsg_ep_alloc_request(struct usb_ep *ep,
						   gfp_t gfp_flags)
{
	struct usbhsg_request *ureq;

	ureq = kzalloc(sizeof *ureq, gfp_flags);
	if (!ureq)
		return NULL;

	usbhs_pkt_init(usbhsg_ureq_to_pkt(ureq));

	return &ureq->req;
}