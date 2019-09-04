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
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct xenvif {int ctrl_irq; TYPE_1__ ctrl; int /*<<< orphan*/  domid; struct net_device* dev; } ;
struct xen_netif_ctrl_sring {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACK_RING_INIT (TYPE_1__*,struct xen_netif_ctrl_sring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int bind_interdomain_evtchn_to_irq (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct xenvif*) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenvif*) ; 
 int xenbus_map_ring_valloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_ctrl_irq_fn ; 
 int /*<<< orphan*/  xenvif_deinit_hash (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_init_hash (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_to_xenbus_device (struct xenvif*) ; 

int xenvif_connect_ctrl(struct xenvif *vif, grant_ref_t ring_ref,
			unsigned int evtchn)
{
	struct net_device *dev = vif->dev;
	void *addr;
	struct xen_netif_ctrl_sring *shared;
	int err;

	err = xenbus_map_ring_valloc(xenvif_to_xenbus_device(vif),
				     &ring_ref, 1, &addr);
	if (err)
		goto err;

	shared = (struct xen_netif_ctrl_sring *)addr;
	BACK_RING_INIT(&vif->ctrl, shared, XEN_PAGE_SIZE);

	err = bind_interdomain_evtchn_to_irq(vif->domid, evtchn);
	if (err < 0)
		goto err_unmap;

	vif->ctrl_irq = err;

	xenvif_init_hash(vif);

	err = request_threaded_irq(vif->ctrl_irq, NULL, xenvif_ctrl_irq_fn,
				   IRQF_ONESHOT, "xen-netback-ctrl", vif);
	if (err) {
		pr_warn("Could not setup irq handler for %s\n", dev->name);
		goto err_deinit;
	}

	return 0;

err_deinit:
	xenvif_deinit_hash(vif);
	unbind_from_irqhandler(vif->ctrl_irq, vif);
	vif->ctrl_irq = 0;

err_unmap:
	xenbus_unmap_ring_vfree(xenvif_to_xenbus_device(vif),
				vif->ctrl.sring);
	vif->ctrl.sring = NULL;

err:
	return err;
}