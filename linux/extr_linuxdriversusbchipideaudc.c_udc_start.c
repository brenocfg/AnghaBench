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
struct usb_otg_caps {scalar_t__ adp_support; scalar_t__ srp_support; scalar_t__ hnp_support; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct ci_hw_td {int dummy; } ;
struct ci_hw_qh {int dummy; } ;
struct TYPE_6__ {int quirk_avoids_skb_reserve; int is_otg; int /*<<< orphan*/  dev; int /*<<< orphan*/ * ep0; int /*<<< orphan*/  ep_list; struct usb_otg_caps* otg_caps; int /*<<< orphan*/  name; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  speed; int /*<<< orphan*/ * ops; } ;
struct ci_hdrc {int /*<<< orphan*/ * qh_pool; int /*<<< orphan*/ * td_pool; TYPE_3__ gadget; TYPE_2__* ep0in; scalar_t__ is_otg; TYPE_1__* platdata; struct device* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  name; struct usb_otg_caps ci_otg_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CI_HDRC_PAGE_SIZE ; 
 int CI_HDRC_REQUIRES_ALIGNED_DMA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_SPEED_HIGH ; 
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  destroy_eps (struct ci_hdrc*) ; 
 void* dma_pool_create (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int init_eps (struct ci_hdrc*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_no_callbacks (int /*<<< orphan*/ *) ; 
 int usb_add_gadget_udc (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  usb_gadget_ops ; 

__attribute__((used)) static int udc_start(struct ci_hdrc *ci)
{
	struct device *dev = ci->dev;
	struct usb_otg_caps *otg_caps = &ci->platdata->ci_otg_caps;
	int retval = 0;

	ci->gadget.ops          = &usb_gadget_ops;
	ci->gadget.speed        = USB_SPEED_UNKNOWN;
	ci->gadget.max_speed    = USB_SPEED_HIGH;
	ci->gadget.name         = ci->platdata->name;
	ci->gadget.otg_caps	= otg_caps;

	if (ci->platdata->flags & CI_HDRC_REQUIRES_ALIGNED_DMA)
		ci->gadget.quirk_avoids_skb_reserve = 1;

	if (ci->is_otg && (otg_caps->hnp_support || otg_caps->srp_support ||
						otg_caps->adp_support))
		ci->gadget.is_otg = 1;

	INIT_LIST_HEAD(&ci->gadget.ep_list);

	/* alloc resources */
	ci->qh_pool = dma_pool_create("ci_hw_qh", dev->parent,
				       sizeof(struct ci_hw_qh),
				       64, CI_HDRC_PAGE_SIZE);
	if (ci->qh_pool == NULL)
		return -ENOMEM;

	ci->td_pool = dma_pool_create("ci_hw_td", dev->parent,
				       sizeof(struct ci_hw_td),
				       64, CI_HDRC_PAGE_SIZE);
	if (ci->td_pool == NULL) {
		retval = -ENOMEM;
		goto free_qh_pool;
	}

	retval = init_eps(ci);
	if (retval)
		goto free_pools;

	ci->gadget.ep0 = &ci->ep0in->ep;

	retval = usb_add_gadget_udc(dev, &ci->gadget);
	if (retval)
		goto destroy_eps;

	pm_runtime_no_callbacks(&ci->gadget.dev);
	pm_runtime_enable(&ci->gadget.dev);

	return retval;

destroy_eps:
	destroy_eps(ci);
free_pools:
	dma_pool_destroy(ci->td_pool);
free_qh_pool:
	dma_pool_destroy(ci->qh_pool);
	return retval;
}