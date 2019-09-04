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
struct TYPE_6__ {int /*<<< orphan*/  ep_list; TYPE_4__* ep0; } ;
struct TYPE_7__ {int /*<<< orphan*/  unusable; int /*<<< orphan*/  reset; int /*<<< orphan*/  shutdown; } ;
struct usbip_device {TYPE_3__ eh_ops; int /*<<< orphan*/  side; int /*<<< orphan*/  status; int /*<<< orphan*/  lock; } ;
struct vudc {int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  urb_queue; int /*<<< orphan*/  lock_tx; int /*<<< orphan*/  lock; TYPE_2__ gadget; struct vep* ep; struct usbip_device ud; } ;
struct TYPE_5__ {int type_control; int dir_out; int dir_in; int type_iso; int type_int; int type_bulk; } ;
struct TYPE_8__ {int max_streams; int /*<<< orphan*/  ep_list; TYPE_1__ caps; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct vep {TYPE_4__ ep; int /*<<< orphan*/  req_queue; TYPE_2__* gadget; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDEV_ST_AVAILABLE ; 
 int /*<<< orphan*/  USBIP_VUDC ; 
 int VIRTUAL_ENDPOINTS ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct vep* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  usb_ep_set_maxpacket_limit (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v_init_timer (struct vudc*) ; 
 int /*<<< orphan*/  vep_ops ; 
 int /*<<< orphan*/  vudc_device_reset ; 
 int /*<<< orphan*/  vudc_device_unusable ; 
 int /*<<< orphan*/  vudc_shutdown ; 

__attribute__((used)) static int init_vudc_hw(struct vudc *udc)
{
	int i;
	struct usbip_device *ud = &udc->ud;
	struct vep *ep;

	udc->ep = kcalloc(VIRTUAL_ENDPOINTS, sizeof(*udc->ep), GFP_KERNEL);
	if (!udc->ep)
		goto nomem_ep;

	INIT_LIST_HEAD(&udc->gadget.ep_list);

	/* create ep0 and 15 in, 15 out general purpose eps */
	for (i = 0; i < VIRTUAL_ENDPOINTS; ++i) {
		int is_out = i % 2;
		int num = (i + 1) / 2;

		ep = &udc->ep[i];

		sprintf(ep->name, "ep%d%s", num,
			i ? (is_out ? "out" : "in") : "");
		ep->ep.name = ep->name;

		ep->ep.ops = &vep_ops;

		usb_ep_set_maxpacket_limit(&ep->ep, ~0);
		ep->ep.max_streams = 16;
		ep->gadget = &udc->gadget;
		INIT_LIST_HEAD(&ep->req_queue);

		if (i == 0) {
			/* ep0 */
			ep->ep.caps.type_control = true;
			ep->ep.caps.dir_out = true;
			ep->ep.caps.dir_in = true;

			udc->gadget.ep0 = &ep->ep;
		} else {
			/* All other eps */
			ep->ep.caps.type_iso = true;
			ep->ep.caps.type_int = true;
			ep->ep.caps.type_bulk = true;

			if (is_out)
				ep->ep.caps.dir_out = true;
			else
				ep->ep.caps.dir_in = true;

			list_add_tail(&ep->ep.ep_list, &udc->gadget.ep_list);
		}
	}

	spin_lock_init(&udc->lock);
	spin_lock_init(&udc->lock_tx);
	INIT_LIST_HEAD(&udc->urb_queue);
	INIT_LIST_HEAD(&udc->tx_queue);
	init_waitqueue_head(&udc->tx_waitq);

	spin_lock_init(&ud->lock);
	ud->status = SDEV_ST_AVAILABLE;
	ud->side = USBIP_VUDC;

	ud->eh_ops.shutdown = vudc_shutdown;
	ud->eh_ops.reset    = vudc_device_reset;
	ud->eh_ops.unusable = vudc_device_unusable;

	v_init_timer(udc);
	return 0;

nomem_ep:
		return -ENOMEM;
}