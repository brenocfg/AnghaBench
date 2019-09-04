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
struct dummy_request {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct dummy_request*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct dummy_request* usb_request_to_dummy_request (struct usb_request*) ; 

__attribute__((used)) static void dummy_free_request(struct usb_ep *_ep, struct usb_request *_req)
{
	struct dummy_request	*req;

	if (!_ep || !_req) {
		WARN_ON(1);
		return;
	}

	req = usb_request_to_dummy_request(_req);
	WARN_ON(!list_empty(&req->queue));
	kfree(req);
}