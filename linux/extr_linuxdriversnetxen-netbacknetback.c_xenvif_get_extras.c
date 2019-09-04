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
struct TYPE_4__ {scalar_t__ req_cons; } ;
struct xenvif_queue {TYPE_1__* vif; TYPE_2__ tx; } ;
struct xen_netif_extra_info {int flags; int type; } ;
typedef  int /*<<< orphan*/  extra ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int EBADR ; 
 int EINVAL ; 
 int /*<<< orphan*/  RING_COPY_REQUEST (TYPE_2__*,scalar_t__,struct xen_netif_extra_info*) ; 
 int XEN_NETIF_EXTRA_FLAG_MORE ; 
 int XEN_NETIF_EXTRA_TYPE_MAX ; 
 int /*<<< orphan*/  memcpy (struct xen_netif_extra_info*,struct xen_netif_extra_info*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xenvif_fatal_tx_err (TYPE_1__*) ; 

__attribute__((used)) static int xenvif_get_extras(struct xenvif_queue *queue,
			     struct xen_netif_extra_info *extras,
			     unsigned int *extra_count,
			     int work_to_do)
{
	struct xen_netif_extra_info extra;
	RING_IDX cons = queue->tx.req_cons;

	do {
		if (unlikely(work_to_do-- <= 0)) {
			netdev_err(queue->vif->dev, "Missing extra info\n");
			xenvif_fatal_tx_err(queue->vif);
			return -EBADR;
		}

		RING_COPY_REQUEST(&queue->tx, cons, &extra);

		queue->tx.req_cons = ++cons;
		(*extra_count)++;

		if (unlikely(!extra.type ||
			     extra.type >= XEN_NETIF_EXTRA_TYPE_MAX)) {
			netdev_err(queue->vif->dev,
				   "Invalid extra type: %d\n", extra.type);
			xenvif_fatal_tx_err(queue->vif);
			return -EINVAL;
		}

		memcpy(&extras[extra.type - 1], &extra, sizeof(extra));
	} while (extra.flags & XEN_NETIF_EXTRA_FLAG_MORE);

	return work_to_do;
}