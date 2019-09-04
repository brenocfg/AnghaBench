#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type_control; int type_iso; int type_bulk; int type_int; int dir_in; int dir_out; } ;
struct TYPE_8__ {int /*<<< orphan*/  ep_list; TYPE_1__ caps; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/  dma; int /*<<< orphan*/  queue; } ;
struct ci_hw_ep {TYPE_4__ ep; TYPE_2__ qh; int /*<<< orphan*/  name; int /*<<< orphan*/  td_pool; int /*<<< orphan*/ * lock; struct ci_hdrc* ci; } ;
struct TYPE_7__ {int /*<<< orphan*/  ep_list; } ;
struct ci_hdrc {int hw_ep_max; TYPE_3__ gadget; struct ci_hw_ep* ep0in; struct ci_hw_ep* ep0out; int /*<<< orphan*/  qh_pool; int /*<<< orphan*/  td_pool; int /*<<< orphan*/  lock; struct ci_hw_ep* ci_hw_ep; } ;

/* Variables and functions */
 unsigned short CTRL_PAYLOAD_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RX ; 
 int TX ; 
 int /*<<< orphan*/ * dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (int /*<<< orphan*/ ,int,char*,int,char*) ; 
 int /*<<< orphan*/  usb_ep_ops ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_4__*,unsigned short) ; 

__attribute__((used)) static int init_eps(struct ci_hdrc *ci)
{
	int retval = 0, i, j;

	for (i = 0; i < ci->hw_ep_max/2; i++)
		for (j = RX; j <= TX; j++) {
			int k = i + j * ci->hw_ep_max/2;
			struct ci_hw_ep *hwep = &ci->ci_hw_ep[k];

			scnprintf(hwep->name, sizeof(hwep->name), "ep%i%s", i,
					(j == TX)  ? "in" : "out");

			hwep->ci          = ci;
			hwep->lock         = &ci->lock;
			hwep->td_pool      = ci->td_pool;

			hwep->ep.name      = hwep->name;
			hwep->ep.ops       = &usb_ep_ops;

			if (i == 0) {
				hwep->ep.caps.type_control = true;
			} else {
				hwep->ep.caps.type_iso = true;
				hwep->ep.caps.type_bulk = true;
				hwep->ep.caps.type_int = true;
			}

			if (j == TX)
				hwep->ep.caps.dir_in = true;
			else
				hwep->ep.caps.dir_out = true;

			/*
			 * for ep0: maxP defined in desc, for other
			 * eps, maxP is set by epautoconfig() called
			 * by gadget layer
			 */
			usb_ep_set_maxpacket_limit(&hwep->ep, (unsigned short)~0);

			INIT_LIST_HEAD(&hwep->qh.queue);
			hwep->qh.ptr = dma_pool_zalloc(ci->qh_pool, GFP_KERNEL,
						       &hwep->qh.dma);
			if (hwep->qh.ptr == NULL)
				retval = -ENOMEM;

			/*
			 * set up shorthands for ep0 out and in endpoints,
			 * don't add to gadget's ep_list
			 */
			if (i == 0) {
				if (j == RX)
					ci->ep0out = hwep;
				else
					ci->ep0in = hwep;

				usb_ep_set_maxpacket_limit(&hwep->ep, CTRL_PAYLOAD_MAX);
				continue;
			}

			list_add_tail(&hwep->ep.ep_list, &ci->gadget.ep_list);
		}

	return retval;
}