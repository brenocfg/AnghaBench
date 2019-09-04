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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; struct net_device* dev; } ;
struct TYPE_2__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {int features; TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct napi_struct {int dummy; } ;
struct mtk_soc_data {int hw_features; int checksum_bit; int mac_count; scalar_t__ dma_type; scalar_t__ rx_sg_dma; scalar_t__ rx_2b_offset; } ;
struct mtk_rx_ring {int rx_calc_idx; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/ ** rx_data; int /*<<< orphan*/  frag_size; struct mtk_rx_dma* rx_dma; } ;
struct mtk_rx_dma {int rxd2; int rxd4; unsigned int rxd1; int /*<<< orphan*/  rxd3; } ;
struct mtk_eth {struct mtk_soc_data* soc; struct net_device** netdev; struct mtk_rx_ring* rx_ring; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ MTK_QDMA ; 
 int /*<<< orphan*/  MTK_QRX_CRX_IDX0 ; 
 int /*<<< orphan*/  MTK_REG_RX_CALC_IDX0 ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 int NEXT_RX_DESP_IDX (int) ; 
 int RX_DMA_DONE ; 
 int RX_DMA_FPORT_MASK ; 
 int RX_DMA_FPORT_SHIFT ; 
 unsigned int RX_DMA_GET_PLEN0 (int) ; 
 int RX_DMA_LSO ; 
 int RX_DMA_PLEN0 (int /*<<< orphan*/ ) ; 
 scalar_t__ RX_DMA_VID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_get_rxd (struct mtk_rx_dma*,struct mtk_rx_dma*) ; 
 int /*<<< orphan*/  mtk_irq_ack (struct mtk_eth*,int) ; 
 int /*<<< orphan*/  mtk_reg_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * napi_alloc_frag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_free_frag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int mtk_poll_rx(struct napi_struct *napi, int budget,
		       struct mtk_eth *eth, u32 rx_intr)
{
	struct mtk_soc_data *soc = eth->soc;
	struct mtk_rx_ring *ring = &eth->rx_ring[0];
	int idx = ring->rx_calc_idx;
	u32 checksum_bit;
	struct sk_buff *skb;
	u8 *data, *new_data;
	struct mtk_rx_dma *rxd, trxd;
	int done = 0, pad;

	if (eth->soc->hw_features & NETIF_F_RXCSUM)
		checksum_bit = soc->checksum_bit;
	else
		checksum_bit = 0;

	if (eth->soc->rx_2b_offset)
		pad = 0;
	else
		pad = NET_IP_ALIGN;

	while (done < budget) {
		struct net_device *netdev;
		unsigned int pktlen;
		dma_addr_t dma_addr;
		int mac = 0;

		idx = NEXT_RX_DESP_IDX(idx);
		rxd = &ring->rx_dma[idx];
		data = ring->rx_data[idx];

		mtk_get_rxd(&trxd, rxd);
		if (!(trxd.rxd2 & RX_DMA_DONE))
			break;

		/* find out which mac the packet come from. values start at 1 */
		if (eth->soc->mac_count > 1) {
			mac = (trxd.rxd4 >> RX_DMA_FPORT_SHIFT) &
			      RX_DMA_FPORT_MASK;
			mac--;
			if (mac < 0 || mac >= eth->soc->mac_count)
				goto release_desc;
		}

		netdev = eth->netdev[mac];

		/* alloc new buffer */
		new_data = napi_alloc_frag(ring->frag_size);
		if (unlikely(!new_data || !netdev)) {
			netdev->stats.rx_dropped++;
			goto release_desc;
		}
		dma_addr = dma_map_single(&netdev->dev,
					  new_data + NET_SKB_PAD + pad,
					  ring->rx_buf_size,
					  DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(&netdev->dev, dma_addr))) {
			skb_free_frag(new_data);
			goto release_desc;
		}

		/* receive data */
		skb = build_skb(data, ring->frag_size);
		if (unlikely(!skb)) {
			put_page(virt_to_head_page(new_data));
			goto release_desc;
		}
		skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);

		dma_unmap_single(&netdev->dev, trxd.rxd1,
				 ring->rx_buf_size, DMA_FROM_DEVICE);
		pktlen = RX_DMA_GET_PLEN0(trxd.rxd2);
		skb->dev = netdev;
		skb_put(skb, pktlen);
		if (trxd.rxd4 & checksum_bit)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		else
			skb_checksum_none_assert(skb);
		skb->protocol = eth_type_trans(skb, netdev);

		netdev->stats.rx_packets++;
		netdev->stats.rx_bytes += pktlen;

		if (netdev->features & NETIF_F_HW_VLAN_CTAG_RX &&
		    RX_DMA_VID(trxd.rxd3))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       RX_DMA_VID(trxd.rxd3));
		napi_gro_receive(napi, skb);

		ring->rx_data[idx] = new_data;
		rxd->rxd1 = (unsigned int)dma_addr;

release_desc:
		if (eth->soc->rx_sg_dma)
			rxd->rxd2 = RX_DMA_PLEN0(ring->rx_buf_size);
		else
			rxd->rxd2 = RX_DMA_LSO;

		ring->rx_calc_idx = idx;
		/* make sure that all changes to the dma ring are flushed before
		 * we continue
		 */
		wmb();
		if (eth->soc->dma_type == MTK_QDMA)
			mtk_w32(eth, ring->rx_calc_idx, MTK_QRX_CRX_IDX0);
		else
			mtk_reg_w32(eth, ring->rx_calc_idx,
				    MTK_REG_RX_CALC_IDX0);
		done++;
	}

	if (done < budget)
		mtk_irq_ack(eth, rx_intr);

	return done;
}