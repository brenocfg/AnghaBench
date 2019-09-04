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
struct TYPE_4__ {scalar_t__ sring; } ;
struct TYPE_3__ {scalar_t__ sring; } ;
struct xenvif_queue {TYPE_2__ rx; int /*<<< orphan*/  vif; TYPE_1__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xenvif_to_xenbus_device (int /*<<< orphan*/ ) ; 

void xenvif_unmap_frontend_data_rings(struct xenvif_queue *queue)
{
	if (queue->tx.sring)
		xenbus_unmap_ring_vfree(xenvif_to_xenbus_device(queue->vif),
					queue->tx.sring);
	if (queue->rx.sring)
		xenbus_unmap_ring_vfree(xenvif_to_xenbus_device(queue->vif),
					queue->rx.sring);
}