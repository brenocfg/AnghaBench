#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_5__ {int /*<<< orphan*/  ep_list; } ;
struct qe_udc {TYPE_2__ gadget; struct qe_ep* eps; } ;
struct TYPE_4__ {int type_control; int type_iso; int type_bulk; int type_int; int dir_in; int dir_out; } ;
struct TYPE_6__ {int /*<<< orphan*/  ep_list; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * ops; TYPE_1__ caps; int /*<<< orphan*/  name; } ;
struct qe_ep {int stopped; int dir; TYPE_2__* gadget; TYPE_3__ ep; int /*<<< orphan*/  queue; scalar_t__ has_data; int /*<<< orphan*/  state; int /*<<< orphan*/ * tx_req; int /*<<< orphan*/ * txframe; int /*<<< orphan*/ * rxframe; scalar_t__ init; scalar_t__ last; scalar_t__ sent; scalar_t__ epnum; int /*<<< orphan*/  name; struct qe_udc* udc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_STATE_IDLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ep_name ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qe_ep_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_3__*,unsigned short) ; 

__attribute__((used)) static int qe_ep_config(struct qe_udc *udc, unsigned char pipe_num)
{
	struct qe_ep *ep = &udc->eps[pipe_num];

	ep->udc = udc;
	strcpy(ep->name, ep_name[pipe_num]);
	ep->ep.name = ep_name[pipe_num];

	if (pipe_num == 0) {
		ep->ep.caps.type_control = true;
	} else {
		ep->ep.caps.type_iso = true;
		ep->ep.caps.type_bulk = true;
		ep->ep.caps.type_int = true;
	}

	ep->ep.caps.dir_in = true;
	ep->ep.caps.dir_out = true;

	ep->ep.ops = &qe_ep_ops;
	ep->stopped = 1;
	usb_ep_set_maxpacket_limit(&ep->ep, (unsigned short) ~0);
	ep->ep.desc = NULL;
	ep->dir = 0xff;
	ep->epnum = (u8)pipe_num;
	ep->sent = 0;
	ep->last = 0;
	ep->init = 0;
	ep->rxframe = NULL;
	ep->txframe = NULL;
	ep->tx_req = NULL;
	ep->state = EP_STATE_IDLE;
	ep->has_data = 0;

	/* the queue lists any req for this ep */
	INIT_LIST_HEAD(&ep->queue);

	/* gagdet.ep_list used for ep_autoconfig so no ep0*/
	if (pipe_num != 0)
		list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);

	ep->gadget = &udc->gadget;

	return 0;
}