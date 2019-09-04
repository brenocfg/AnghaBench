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
struct TYPE_2__ {scalar_t__ req_cons; } ;
struct xenvif_queue {TYPE_1__ tx; int /*<<< orphan*/  response_lock; } ;
struct xen_netif_tx_request {int dummy; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  RING_COPY_REQUEST (TYPE_1__*,int /*<<< orphan*/ ,struct xen_netif_tx_request*) ; 
 int /*<<< orphan*/  XEN_NETIF_RSP_ERROR ; 
 int /*<<< orphan*/  make_tx_response (struct xenvif_queue*,struct xen_netif_tx_request*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_tx_responses (struct xenvif_queue*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void xenvif_tx_err(struct xenvif_queue *queue,
			  struct xen_netif_tx_request *txp,
			  unsigned int extra_count, RING_IDX end)
{
	RING_IDX cons = queue->tx.req_cons;
	unsigned long flags;

	do {
		spin_lock_irqsave(&queue->response_lock, flags);
		make_tx_response(queue, txp, extra_count, XEN_NETIF_RSP_ERROR);
		push_tx_responses(queue);
		spin_unlock_irqrestore(&queue->response_lock, flags);
		if (cons == end)
			break;
		RING_COPY_REQUEST(&queue->tx, cons++, txp);
		extra_count = 0; /* only the first frag can have extras */
	} while (1);
	queue->tx.req_cons = cons;
}