#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  union Vmxnet3_GenericDesc {int dummy; } Vmxnet3_GenericDesc ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_18__ {size_t next2proc; scalar_t__ gen; TYPE_6__* base; } ;
struct TYPE_13__ {int /*<<< orphan*/  rx_buf_alloc_failure; int /*<<< orphan*/  drop_total; } ;
struct TYPE_12__ {int desc_size; int /*<<< orphan*/ * base; } ;
struct vmxnet3_rx_ctx {struct sk_buff* skb; } ;
struct vmxnet3_rx_queue {scalar_t__ qid; scalar_t__ qid2; scalar_t__ dataRingQid; TYPE_7__ comp_ring; TYPE_5__* shared; struct vmxnet3_cmd_ring* rx_ring; int /*<<< orphan*/  napi; TYPE_2__ stats; TYPE_1__ data_ring; struct vmxnet3_rx_buf_info** buf_info; struct vmxnet3_rx_ctx rx_ctx; } ;
struct vmxnet3_rx_buf_info {scalar_t__ dma_addr; scalar_t__ len; scalar_t__ buf_type; struct page* page; struct sk_buff* skb; } ;
struct vmxnet3_cmd_ring {int next2comp; size_t next2fill; int /*<<< orphan*/  gen; TYPE_4__* base; } ;
struct vmxnet3_adapter {TYPE_9__* netdev; TYPE_3__* pdev; } ;
struct sk_buff {int len; int data_len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct page {int dummy; } ;
struct Vmxnet3_RxDesc {scalar_t__ addr; scalar_t__ len; scalar_t__ btype; int /*<<< orphan*/  gen; } ;
struct Vmxnet3_RxCompDescExt {int segCnt; int mss; } ;
struct Vmxnet3_RxCompDesc {scalar_t__ gen; scalar_t__ rqID; int rxdIdx; int len; scalar_t__ type; int ts; int /*<<< orphan*/  tci; scalar_t__ v4; int /*<<< orphan*/  tcp; scalar_t__ eop; scalar_t__ sop; scalar_t__ err; } ;
typedef  void* dma_addr_t ;
struct TYPE_20__ {int mtu; int features; } ;
struct TYPE_19__ {int gso_size; int gso_segs; void* gso_type; } ;
struct TYPE_17__ {int /*<<< orphan*/  rcd; } ;
struct TYPE_16__ {int updateRxProd; } ;
struct TYPE_15__ {int /*<<< orphan*/  rxd; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 void* SKB_GSO_TCPV4 ; 
 void* SKB_GSO_TCPV6 ; 
 scalar_t__ VMXNET3_CDTYPE_RXCOMP_LRO ; 
 int VMXNET3_GET_RING_IDX (struct vmxnet3_adapter*,scalar_t__) ; 
#define  VMXNET3_REG_RXPROD 129 
#define  VMXNET3_REG_RXPROD2 128 
 scalar_t__ VMXNET3_RXD_BTYPE_BODY ; 
 scalar_t__ VMXNET3_RXD_BTYPE_HEAD ; 
 scalar_t__ VMXNET3_RX_BUF_PAGE ; 
 scalar_t__ VMXNET3_RX_BUF_SKB ; 
 int VMXNET3_RX_DATA_RING (struct vmxnet3_adapter*,scalar_t__) ; 
 scalar_t__ VMXNET3_VERSION_GE_2 (struct vmxnet3_adapter*) ; 
 int /*<<< orphan*/  VMXNET3_WRITE_BAR0_REG (struct vmxnet3_adapter*,int const,size_t) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 void* dma_map_page (int /*<<< orphan*/ *,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_9__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_9__*,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_9__*,char*,int,int) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  rxCmdDesc ; 
 int /*<<< orphan*/  rxComp ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 TYPE_8__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmxnet3_append_frag (struct sk_buff*,struct Vmxnet3_RxCompDesc*,struct vmxnet3_rx_buf_info*) ; 
 int /*<<< orphan*/  vmxnet3_cmd_ring_adv_next2fill (struct vmxnet3_cmd_ring*) ; 
 int vmxnet3_cmd_ring_desc_avail (struct vmxnet3_cmd_ring*) ; 
 int /*<<< orphan*/  vmxnet3_comp_ring_adv_next2proc (TYPE_7__*) ; 
 int /*<<< orphan*/  vmxnet3_getRxComp (struct Vmxnet3_RxCompDesc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmxnet3_getRxDesc (struct Vmxnet3_RxDesc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vmxnet3_get_hdr_len (struct vmxnet3_adapter*,struct sk_buff*,union Vmxnet3_GenericDesc*) ; 
 int /*<<< orphan*/  vmxnet3_rx_csum (struct vmxnet3_adapter*,struct sk_buff*,union Vmxnet3_GenericDesc*) ; 
 int /*<<< orphan*/  vmxnet3_rx_error (struct vmxnet3_rx_queue*,struct Vmxnet3_RxCompDesc*,struct vmxnet3_rx_ctx*,struct vmxnet3_adapter*) ; 

__attribute__((used)) static int
vmxnet3_rq_rx_complete(struct vmxnet3_rx_queue *rq,
		       struct vmxnet3_adapter *adapter, int quota)
{
	static const u32 rxprod_reg[2] = {
		VMXNET3_REG_RXPROD, VMXNET3_REG_RXPROD2
	};
	u32 num_pkts = 0;
	bool skip_page_frags = false;
	struct Vmxnet3_RxCompDesc *rcd;
	struct vmxnet3_rx_ctx *ctx = &rq->rx_ctx;
	u16 segCnt = 0, mss = 0;
#ifdef __BIG_ENDIAN_BITFIELD
	struct Vmxnet3_RxDesc rxCmdDesc;
	struct Vmxnet3_RxCompDesc rxComp;
#endif
	vmxnet3_getRxComp(rcd, &rq->comp_ring.base[rq->comp_ring.next2proc].rcd,
			  &rxComp);
	while (rcd->gen == rq->comp_ring.gen) {
		struct vmxnet3_rx_buf_info *rbi;
		struct sk_buff *skb, *new_skb = NULL;
		struct page *new_page = NULL;
		dma_addr_t new_dma_addr;
		int num_to_alloc;
		struct Vmxnet3_RxDesc *rxd;
		u32 idx, ring_idx;
		struct vmxnet3_cmd_ring	*ring = NULL;
		if (num_pkts >= quota) {
			/* we may stop even before we see the EOP desc of
			 * the current pkt
			 */
			break;
		}

		/* Prevent any rcd field from being (speculatively) read before
		 * rcd->gen is read.
		 */
		dma_rmb();

		BUG_ON(rcd->rqID != rq->qid && rcd->rqID != rq->qid2 &&
		       rcd->rqID != rq->dataRingQid);
		idx = rcd->rxdIdx;
		ring_idx = VMXNET3_GET_RING_IDX(adapter, rcd->rqID);
		ring = rq->rx_ring + ring_idx;
		vmxnet3_getRxDesc(rxd, &rq->rx_ring[ring_idx].base[idx].rxd,
				  &rxCmdDesc);
		rbi = rq->buf_info[ring_idx] + idx;

		BUG_ON(rxd->addr != rbi->dma_addr ||
		       rxd->len != rbi->len);

		if (unlikely(rcd->eop && rcd->err)) {
			vmxnet3_rx_error(rq, rcd, ctx, adapter);
			goto rcd_done;
		}

		if (rcd->sop) { /* first buf of the pkt */
			bool rxDataRingUsed;
			u16 len;

			BUG_ON(rxd->btype != VMXNET3_RXD_BTYPE_HEAD ||
			       (rcd->rqID != rq->qid &&
				rcd->rqID != rq->dataRingQid));

			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_SKB);
			BUG_ON(ctx->skb != NULL || rbi->skb == NULL);

			if (unlikely(rcd->len == 0)) {
				/* Pretend the rx buffer is skipped. */
				BUG_ON(!(rcd->sop && rcd->eop));
				netdev_dbg(adapter->netdev,
					"rxRing[%u][%u] 0 length\n",
					ring_idx, idx);
				goto rcd_done;
			}

			skip_page_frags = false;
			ctx->skb = rbi->skb;

			rxDataRingUsed =
				VMXNET3_RX_DATA_RING(adapter, rcd->rqID);
			len = rxDataRingUsed ? rcd->len : rbi->len;
			new_skb = netdev_alloc_skb_ip_align(adapter->netdev,
							    len);
			if (new_skb == NULL) {
				/* Skb allocation failed, do not handover this
				 * skb to stack. Reuse it. Drop the existing pkt
				 */
				rq->stats.rx_buf_alloc_failure++;
				ctx->skb = NULL;
				rq->stats.drop_total++;
				skip_page_frags = true;
				goto rcd_done;
			}

			if (rxDataRingUsed) {
				size_t sz;

				BUG_ON(rcd->len > rq->data_ring.desc_size);

				ctx->skb = new_skb;
				sz = rcd->rxdIdx * rq->data_ring.desc_size;
				memcpy(new_skb->data,
				       &rq->data_ring.base[sz], rcd->len);
			} else {
				ctx->skb = rbi->skb;

				new_dma_addr =
					dma_map_single(&adapter->pdev->dev,
						       new_skb->data, rbi->len,
						       PCI_DMA_FROMDEVICE);
				if (dma_mapping_error(&adapter->pdev->dev,
						      new_dma_addr)) {
					dev_kfree_skb(new_skb);
					/* Skb allocation failed, do not
					 * handover this skb to stack. Reuse
					 * it. Drop the existing pkt.
					 */
					rq->stats.rx_buf_alloc_failure++;
					ctx->skb = NULL;
					rq->stats.drop_total++;
					skip_page_frags = true;
					goto rcd_done;
				}

				dma_unmap_single(&adapter->pdev->dev,
						 rbi->dma_addr,
						 rbi->len,
						 PCI_DMA_FROMDEVICE);

				/* Immediate refill */
				rbi->skb = new_skb;
				rbi->dma_addr = new_dma_addr;
				rxd->addr = cpu_to_le64(rbi->dma_addr);
				rxd->len = rbi->len;
			}

#ifdef VMXNET3_RSS
			if (rcd->rssType != VMXNET3_RCD_RSS_TYPE_NONE &&
			    (adapter->netdev->features & NETIF_F_RXHASH))
				skb_set_hash(ctx->skb,
					     le32_to_cpu(rcd->rssHash),
					     PKT_HASH_TYPE_L3);
#endif
			skb_put(ctx->skb, rcd->len);

			if (VMXNET3_VERSION_GE_2(adapter) &&
			    rcd->type == VMXNET3_CDTYPE_RXCOMP_LRO) {
				struct Vmxnet3_RxCompDescExt *rcdlro;
				rcdlro = (struct Vmxnet3_RxCompDescExt *)rcd;

				segCnt = rcdlro->segCnt;
				WARN_ON_ONCE(segCnt == 0);
				mss = rcdlro->mss;
				if (unlikely(segCnt <= 1))
					segCnt = 0;
			} else {
				segCnt = 0;
			}
		} else {
			BUG_ON(ctx->skb == NULL && !skip_page_frags);

			/* non SOP buffer must be type 1 in most cases */
			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_PAGE);
			BUG_ON(rxd->btype != VMXNET3_RXD_BTYPE_BODY);

			/* If an sop buffer was dropped, skip all
			 * following non-sop fragments. They will be reused.
			 */
			if (skip_page_frags)
				goto rcd_done;

			if (rcd->len) {
				new_page = alloc_page(GFP_ATOMIC);
				/* Replacement page frag could not be allocated.
				 * Reuse this page. Drop the pkt and free the
				 * skb which contained this page as a frag. Skip
				 * processing all the following non-sop frags.
				 */
				if (unlikely(!new_page)) {
					rq->stats.rx_buf_alloc_failure++;
					dev_kfree_skb(ctx->skb);
					ctx->skb = NULL;
					skip_page_frags = true;
					goto rcd_done;
				}
				new_dma_addr = dma_map_page(&adapter->pdev->dev,
							    new_page,
							    0, PAGE_SIZE,
							    PCI_DMA_FROMDEVICE);
				if (dma_mapping_error(&adapter->pdev->dev,
						      new_dma_addr)) {
					put_page(new_page);
					rq->stats.rx_buf_alloc_failure++;
					dev_kfree_skb(ctx->skb);
					ctx->skb = NULL;
					skip_page_frags = true;
					goto rcd_done;
				}

				dma_unmap_page(&adapter->pdev->dev,
					       rbi->dma_addr, rbi->len,
					       PCI_DMA_FROMDEVICE);

				vmxnet3_append_frag(ctx->skb, rcd, rbi);

				/* Immediate refill */
				rbi->page = new_page;
				rbi->dma_addr = new_dma_addr;
				rxd->addr = cpu_to_le64(rbi->dma_addr);
				rxd->len = rbi->len;
			}
		}


		skb = ctx->skb;
		if (rcd->eop) {
			u32 mtu = adapter->netdev->mtu;
			skb->len += skb->data_len;

			vmxnet3_rx_csum(adapter, skb,
					(union Vmxnet3_GenericDesc *)rcd);
			skb->protocol = eth_type_trans(skb, adapter->netdev);
			if (!rcd->tcp ||
			    !(adapter->netdev->features & NETIF_F_LRO))
				goto not_lro;

			if (segCnt != 0 && mss != 0) {
				skb_shinfo(skb)->gso_type = rcd->v4 ?
					SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
				skb_shinfo(skb)->gso_size = mss;
				skb_shinfo(skb)->gso_segs = segCnt;
			} else if (segCnt != 0 || skb->len > mtu) {
				u32 hlen;

				hlen = vmxnet3_get_hdr_len(adapter, skb,
					(union Vmxnet3_GenericDesc *)rcd);
				if (hlen == 0)
					goto not_lro;

				skb_shinfo(skb)->gso_type =
					rcd->v4 ? SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
				if (segCnt != 0) {
					skb_shinfo(skb)->gso_segs = segCnt;
					skb_shinfo(skb)->gso_size =
						DIV_ROUND_UP(skb->len -
							hlen, segCnt);
				} else {
					skb_shinfo(skb)->gso_size = mtu - hlen;
				}
			}
not_lro:
			if (unlikely(rcd->ts))
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rcd->tci);

			if (adapter->netdev->features & NETIF_F_LRO)
				netif_receive_skb(skb);
			else
				napi_gro_receive(&rq->napi, skb);

			ctx->skb = NULL;
			num_pkts++;
		}

rcd_done:
		/* device may have skipped some rx descs */
		ring->next2comp = idx;
		num_to_alloc = vmxnet3_cmd_ring_desc_avail(ring);
		ring = rq->rx_ring + ring_idx;

		/* Ensure that the writes to rxd->gen bits will be observed
		 * after all other writes to rxd objects.
		 */
		dma_wmb();

		while (num_to_alloc) {
			vmxnet3_getRxDesc(rxd, &ring->base[ring->next2fill].rxd,
					  &rxCmdDesc);
			BUG_ON(!rxd->addr);

			/* Recv desc is ready to be used by the device */
			rxd->gen = ring->gen;
			vmxnet3_cmd_ring_adv_next2fill(ring);
			num_to_alloc--;
		}

		/* if needed, update the register */
		if (unlikely(rq->shared->updateRxProd)) {
			VMXNET3_WRITE_BAR0_REG(adapter,
					       rxprod_reg[ring_idx] + rq->qid * 8,
					       ring->next2fill);
		}

		vmxnet3_comp_ring_adv_next2proc(&rq->comp_ring);
		vmxnet3_getRxComp(rcd,
				  &rq->comp_ring.base[rq->comp_ring.next2proc].rcd, &rxComp);
	}

	return num_pkts;
}