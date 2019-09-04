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
struct usb_ep {int dummy; } ;
struct dwc2_hsotg_req {struct usb_request req; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct dwc2_hsotg_req* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct usb_request *dwc2_hsotg_ep_alloc_request(struct usb_ep *ep,
						       gfp_t flags)
{
	struct dwc2_hsotg_req *req;

	req = kzalloc(sizeof(*req), flags);
	if (!req)
		return NULL;

	INIT_LIST_HEAD(&req->queue);

	return &req->req;
}