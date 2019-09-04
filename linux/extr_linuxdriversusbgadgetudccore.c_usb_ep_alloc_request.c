#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_request {int dummy; } ;
struct usb_ep {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct usb_request* (* alloc_request ) (struct usb_ep*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_request* stub1 (struct usb_ep*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_usb_ep_alloc_request (struct usb_ep*,struct usb_request*,int /*<<< orphan*/ ) ; 

struct usb_request *usb_ep_alloc_request(struct usb_ep *ep,
						       gfp_t gfp_flags)
{
	struct usb_request *req = NULL;

	req = ep->ops->alloc_request(ep, gfp_flags);

	trace_usb_ep_alloc_request(ep, req, req ? 0 : -ENOMEM);

	return req;
}