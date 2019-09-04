#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {scalar_t__ next2proc; void* gen; } ;
struct vmxnet3_rx_queue {TYPE_5__ comp_ring; TYPE_4__* rx_ring; TYPE_3__** buf_info; } ;
struct vmxnet3_adapter {TYPE_2__* pdev; } ;
struct Vmxnet3_RxDesc {scalar_t__ btype; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {int size; scalar_t__ next2comp; scalar_t__ next2fill; void* gen; TYPE_1__* base; } ;
struct TYPE_8__ {int /*<<< orphan*/ * page; int /*<<< orphan*/ * skb; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  rxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 void* VMXNET3_INIT_GEN ; 
 scalar_t__ VMXNET3_RXD_BTYPE_BODY ; 
 scalar_t__ VMXNET3_RXD_BTYPE_HEAD ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxDesc ; 
 int /*<<< orphan*/  vmxnet3_getRxDesc (struct Vmxnet3_RxDesc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmxnet3_rq_cleanup(struct vmxnet3_rx_queue *rq,
		   struct vmxnet3_adapter *adapter)
{
	u32 i, ring_idx;
	struct Vmxnet3_RxDesc *rxd;

	for (ring_idx = 0; ring_idx < 2; ring_idx++) {
		for (i = 0; i < rq->rx_ring[ring_idx].size; i++) {
#ifdef __BIG_ENDIAN_BITFIELD
			struct Vmxnet3_RxDesc rxDesc;
#endif
			vmxnet3_getRxDesc(rxd,
				&rq->rx_ring[ring_idx].base[i].rxd, &rxDesc);

			if (rxd->btype == VMXNET3_RXD_BTYPE_HEAD &&
					rq->buf_info[ring_idx][i].skb) {
				dma_unmap_single(&adapter->pdev->dev, rxd->addr,
						 rxd->len, PCI_DMA_FROMDEVICE);
				dev_kfree_skb(rq->buf_info[ring_idx][i].skb);
				rq->buf_info[ring_idx][i].skb = NULL;
			} else if (rxd->btype == VMXNET3_RXD_BTYPE_BODY &&
					rq->buf_info[ring_idx][i].page) {
				dma_unmap_page(&adapter->pdev->dev, rxd->addr,
					       rxd->len, PCI_DMA_FROMDEVICE);
				put_page(rq->buf_info[ring_idx][i].page);
				rq->buf_info[ring_idx][i].page = NULL;
			}
		}

		rq->rx_ring[ring_idx].gen = VMXNET3_INIT_GEN;
		rq->rx_ring[ring_idx].next2fill =
					rq->rx_ring[ring_idx].next2comp = 0;
	}

	rq->comp_ring.gen = VMXNET3_INIT_GEN;
	rq->comp_ring.next2proc = 0;
}