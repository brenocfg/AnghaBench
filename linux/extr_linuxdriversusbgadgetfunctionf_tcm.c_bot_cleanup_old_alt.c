#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/ * req; } ;
struct TYPE_3__ {int /*<<< orphan*/ * req; } ;
struct f_uas {int flags; TYPE_2__ cmd; TYPE_1__ bot_status; int /*<<< orphan*/ * bot_req_out; int /*<<< orphan*/ * bot_req_in; int /*<<< orphan*/  ep_in; int /*<<< orphan*/  ep_out; } ;

/* Variables and functions */
 int USBG_ENABLED ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_free_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bot_cleanup_old_alt(struct f_uas *fu)
{
	if (!(fu->flags & USBG_ENABLED))
		return;

	usb_ep_disable(fu->ep_in);
	usb_ep_disable(fu->ep_out);

	if (!fu->bot_req_in)
		return;

	usb_ep_free_request(fu->ep_in, fu->bot_req_in);
	usb_ep_free_request(fu->ep_out, fu->bot_req_out);
	usb_ep_free_request(fu->ep_out, fu->cmd.req);
	usb_ep_free_request(fu->ep_in, fu->bot_status.req);

	kfree(fu->cmd.buf);

	fu->bot_req_in = NULL;
	fu->bot_req_out = NULL;
	fu->cmd.req = NULL;
	fu->bot_status.req = NULL;
	fu->cmd.buf = NULL;
}