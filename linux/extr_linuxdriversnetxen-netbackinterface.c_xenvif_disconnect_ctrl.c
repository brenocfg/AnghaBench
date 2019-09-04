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
struct xenvif {TYPE_1__ ctrl; scalar_t__ ctrl_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  unbind_from_irqhandler (scalar_t__,struct xenvif*) ; 
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenvif_deinit_hash (struct xenvif*) ; 
 int /*<<< orphan*/  xenvif_to_xenbus_device (struct xenvif*) ; 

void xenvif_disconnect_ctrl(struct xenvif *vif)
{
	if (vif->ctrl_irq) {
		xenvif_deinit_hash(vif);
		unbind_from_irqhandler(vif->ctrl_irq, vif);
		vif->ctrl_irq = 0;
	}

	if (vif->ctrl.sring) {
		xenbus_unmap_ring_vfree(xenvif_to_xenbus_device(vif),
					vif->ctrl.sring);
		vif->ctrl.sring = NULL;
	}
}