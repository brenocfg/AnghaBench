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
struct platform_device {int dummy; } ;
struct gr_udc {int nepo; int nepi; TYPE_4__* ep0reqo; TYPE_3__* epo; TYPE_2__* ep0reqi; TYPE_1__* epi; int /*<<< orphan*/  desc_pool; scalar_t__ driver; int /*<<< orphan*/  gadget; scalar_t__ added; } ;
struct TYPE_8__ {int /*<<< orphan*/  req; } ;
struct TYPE_7__ {int /*<<< orphan*/  ep; } ;
struct TYPE_6__ {int /*<<< orphan*/  req; } ;
struct TYPE_5__ {int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gr_dfs_delete (struct gr_udc*) ; 
 int /*<<< orphan*/  gr_ep_remove (struct gr_udc*,int,int) ; 
 int /*<<< orphan*/  gr_free_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct gr_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gr_remove(struct platform_device *pdev)
{
	struct gr_udc *dev = platform_get_drvdata(pdev);
	int i;

	if (dev->added)
		usb_del_gadget_udc(&dev->gadget); /* Shuts everything down */
	if (dev->driver)
		return -EBUSY;

	gr_dfs_delete(dev);
	dma_pool_destroy(dev->desc_pool);
	platform_set_drvdata(pdev, NULL);

	gr_free_request(&dev->epi[0].ep, &dev->ep0reqi->req);
	gr_free_request(&dev->epo[0].ep, &dev->ep0reqo->req);

	for (i = 0; i < dev->nepo; i++)
		gr_ep_remove(dev, i, 0);
	for (i = 0; i < dev->nepi; i++)
		gr_ep_remove(dev, i, 1);

	return 0;
}