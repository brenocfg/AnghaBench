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
struct TYPE_4__ {int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_2__ base; } ;
struct usbip_device {int dummy; } ;
struct stub_priv {int /*<<< orphan*/  list; struct stub_device* sdev; int /*<<< orphan*/  seqnum; } ;
struct stub_device {int /*<<< orphan*/  priv_lock; int /*<<< orphan*/  priv_init; TYPE_1__* udev; struct usbip_device ud; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SDEV_EVENT_ERROR_MALLOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct stub_priv* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub_priv_cache ; 
 int /*<<< orphan*/  usbip_event_add (struct usbip_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct stub_priv *stub_priv_alloc(struct stub_device *sdev,
					 struct usbip_header *pdu)
{
	struct stub_priv *priv;
	struct usbip_device *ud = &sdev->ud;
	unsigned long flags;

	spin_lock_irqsave(&sdev->priv_lock, flags);

	priv = kmem_cache_zalloc(stub_priv_cache, GFP_ATOMIC);
	if (!priv) {
		dev_err(&sdev->udev->dev, "alloc stub_priv\n");
		spin_unlock_irqrestore(&sdev->priv_lock, flags);
		usbip_event_add(ud, SDEV_EVENT_ERROR_MALLOC);
		return NULL;
	}

	priv->seqnum = pdu->base.seqnum;
	priv->sdev = sdev;

	/*
	 * After a stub_priv is linked to a list_head,
	 * our error handler can free allocated data.
	 */
	list_add_tail(&priv->list, &sdev->priv_init);

	spin_unlock_irqrestore(&sdev->priv_lock, flags);

	return priv;
}