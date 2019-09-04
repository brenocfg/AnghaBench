#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xenvif_queue {int dummy; } ;
struct xenvif_pkt_state {scalar_t__ extra_count; struct xen_netif_extra_info* extras; } ;
struct xen_netif_rx_response {int dummy; } ;
struct xen_netif_rx_request {int dummy; } ;
struct xen_netif_extra_info {scalar_t__ type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct xen_netif_extra_info*) ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  XEN_NETIF_EXTRA_FLAG_MORE ; 

__attribute__((used)) static void xenvif_rx_extra_slot(struct xenvif_queue *queue,
				 struct xenvif_pkt_state *pkt,
				 struct xen_netif_rx_request *req,
				 struct xen_netif_rx_response *rsp)
{
	struct xen_netif_extra_info *extra = (void *)rsp;
	unsigned int i;

	pkt->extra_count--;

	for (i = 0; i < ARRAY_SIZE(pkt->extras); i++) {
		if (pkt->extras[i].type) {
			*extra = pkt->extras[i];

			if (pkt->extra_count != 0)
				extra->flags |= XEN_NETIF_EXTRA_FLAG_MORE;

			pkt->extras[i].type = 0;
			return;
		}
	}
	BUG();
}