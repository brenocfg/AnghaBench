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
struct xenvif_pkt_state {scalar_t__ remaining_len; scalar_t__ slot; scalar_t__ extra_count; struct sk_buff* skb; } ;
struct xen_netif_rx_response {unsigned int flags; scalar_t__ status; int /*<<< orphan*/  id; int /*<<< orphan*/  offset; } ;
struct xen_netif_rx_request {int /*<<< orphan*/  id; } ;
struct sk_buff {scalar_t__ ip_summed; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ CHECKSUM_UNNECESSARY ; 
 unsigned int XEN_NETRXF_csum_blank ; 
 unsigned int XEN_NETRXF_data_validated ; 
 unsigned int XEN_NETRXF_extra_info ; 
 unsigned int XEN_NETRXF_more_data ; 
 unsigned int XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  xenvif_rx_copy_add (struct xenvif_queue*,struct xen_netif_rx_request*,unsigned int,void*,size_t) ; 
 int /*<<< orphan*/  xenvif_rx_next_chunk (struct xenvif_queue*,struct xenvif_pkt_state*,unsigned int,void**,size_t*) ; 

__attribute__((used)) static void xenvif_rx_data_slot(struct xenvif_queue *queue,
				struct xenvif_pkt_state *pkt,
				struct xen_netif_rx_request *req,
				struct xen_netif_rx_response *rsp)
{
	unsigned int offset = 0;
	unsigned int flags;

	do {
		size_t len;
		void *data;

		xenvif_rx_next_chunk(queue, pkt, offset, &data, &len);
		xenvif_rx_copy_add(queue, req, offset, data, len);

		offset += len;
		pkt->remaining_len -= len;

	} while (offset < XEN_PAGE_SIZE && pkt->remaining_len > 0);

	if (pkt->remaining_len > 0)
		flags = XEN_NETRXF_more_data;
	else
		flags = 0;

	if (pkt->slot == 0) {
		struct sk_buff *skb = pkt->skb;

		if (skb->ip_summed == CHECKSUM_PARTIAL)
			flags |= XEN_NETRXF_csum_blank |
				 XEN_NETRXF_data_validated;
		else if (skb->ip_summed == CHECKSUM_UNNECESSARY)
			flags |= XEN_NETRXF_data_validated;

		if (pkt->extra_count != 0)
			flags |= XEN_NETRXF_extra_info;
	}

	rsp->offset = 0;
	rsp->flags = flags;
	rsp->id = req->id;
	rsp->status = (s16)offset;
}