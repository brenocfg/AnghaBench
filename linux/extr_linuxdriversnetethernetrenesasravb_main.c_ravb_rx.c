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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  protocol; } ;
struct ravb_private {int* cur_rx; int* num_rx_ring; int* dirty_rx; int tstamp_rx_ctrl; struct sk_buff*** rx_skb; scalar_t__ rx_buf_sz; struct ravb_ex_rx_desc** rx_ring; int /*<<< orphan*/ * napi; struct net_device_stats* stats; } ;
struct ravb_ex_rx_desc {scalar_t__ die_dt; int msc; int /*<<< orphan*/  dptr; void* ds_cc; int /*<<< orphan*/  ts_n; int /*<<< orphan*/  ts_sl; void* ts_sh; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_missed_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  multicast; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {int features; TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ DT_FEMPTY ; 
 int MSC_CEEF ; 
 int MSC_CRC ; 
 int MSC_MC ; 
 int MSC_RFE ; 
 int MSC_RTLF ; 
 int MSC_RTSF ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ RAVB_ALIGN ; 
 int RAVB_NC ; 
 int RAVB_RXTSTAMP_TYPE ; 
 int RAVB_RXTSTAMP_TYPE_V2_L2_EVENT ; 
 int RX_DS ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le16_to_cpu (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 struct ravb_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ravb_rx_csum (struct sk_buff*) ; 
 int /*<<< orphan*/  ravb_set_buffer_align (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  timespec64_to_ktime (struct timespec64) ; 

__attribute__((used)) static bool ravb_rx(struct net_device *ndev, int *quota, int q)
{
	struct ravb_private *priv = netdev_priv(ndev);
	int entry = priv->cur_rx[q] % priv->num_rx_ring[q];
	int boguscnt = (priv->dirty_rx[q] + priv->num_rx_ring[q]) -
			priv->cur_rx[q];
	struct net_device_stats *stats = &priv->stats[q];
	struct ravb_ex_rx_desc *desc;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	struct timespec64 ts;
	u8  desc_status;
	u16 pkt_len;
	int limit;

	boguscnt = min(boguscnt, *quota);
	limit = boguscnt;
	desc = &priv->rx_ring[q][entry];
	while (desc->die_dt != DT_FEMPTY) {
		/* Descriptor type must be checked before all other reads */
		dma_rmb();
		desc_status = desc->msc;
		pkt_len = le16_to_cpu(desc->ds_cc) & RX_DS;

		if (--boguscnt < 0)
			break;

		/* We use 0-byte descriptors to mark the DMA mapping errors */
		if (!pkt_len)
			continue;

		if (desc_status & MSC_MC)
			stats->multicast++;

		if (desc_status & (MSC_CRC | MSC_RFE | MSC_RTSF | MSC_RTLF |
				   MSC_CEEF)) {
			stats->rx_errors++;
			if (desc_status & MSC_CRC)
				stats->rx_crc_errors++;
			if (desc_status & MSC_RFE)
				stats->rx_frame_errors++;
			if (desc_status & (MSC_RTLF | MSC_RTSF))
				stats->rx_length_errors++;
			if (desc_status & MSC_CEEF)
				stats->rx_missed_errors++;
		} else {
			u32 get_ts = priv->tstamp_rx_ctrl & RAVB_RXTSTAMP_TYPE;

			skb = priv->rx_skb[q][entry];
			priv->rx_skb[q][entry] = NULL;
			dma_unmap_single(ndev->dev.parent, le32_to_cpu(desc->dptr),
					 priv->rx_buf_sz,
					 DMA_FROM_DEVICE);
			get_ts &= (q == RAVB_NC) ?
					RAVB_RXTSTAMP_TYPE_V2_L2_EVENT :
					~RAVB_RXTSTAMP_TYPE_V2_L2_EVENT;
			if (get_ts) {
				struct skb_shared_hwtstamps *shhwtstamps;

				shhwtstamps = skb_hwtstamps(skb);
				memset(shhwtstamps, 0, sizeof(*shhwtstamps));
				ts.tv_sec = ((u64) le16_to_cpu(desc->ts_sh) <<
					     32) | le32_to_cpu(desc->ts_sl);
				ts.tv_nsec = le32_to_cpu(desc->ts_n);
				shhwtstamps->hwtstamp = timespec64_to_ktime(ts);
			}

			skb_put(skb, pkt_len);
			skb->protocol = eth_type_trans(skb, ndev);
			if (ndev->features & NETIF_F_RXCSUM)
				ravb_rx_csum(skb);
			napi_gro_receive(&priv->napi[q], skb);
			stats->rx_packets++;
			stats->rx_bytes += pkt_len;
		}

		entry = (++priv->cur_rx[q]) % priv->num_rx_ring[q];
		desc = &priv->rx_ring[q][entry];
	}

	/* Refill the RX ring buffers. */
	for (; priv->cur_rx[q] - priv->dirty_rx[q] > 0; priv->dirty_rx[q]++) {
		entry = priv->dirty_rx[q] % priv->num_rx_ring[q];
		desc = &priv->rx_ring[q][entry];
		desc->ds_cc = cpu_to_le16(priv->rx_buf_sz);

		if (!priv->rx_skb[q][entry]) {
			skb = netdev_alloc_skb(ndev,
					       priv->rx_buf_sz +
					       RAVB_ALIGN - 1);
			if (!skb)
				break;	/* Better luck next round. */
			ravb_set_buffer_align(skb);
			dma_addr = dma_map_single(ndev->dev.parent, skb->data,
						  le16_to_cpu(desc->ds_cc),
						  DMA_FROM_DEVICE);
			skb_checksum_none_assert(skb);
			/* We just set the data size to 0 for a failed mapping
			 * which should prevent DMA  from happening...
			 */
			if (dma_mapping_error(ndev->dev.parent, dma_addr))
				desc->ds_cc = cpu_to_le16(0);
			desc->dptr = cpu_to_le32(dma_addr);
			priv->rx_skb[q][entry] = skb;
		}
		/* Descriptor type must be set after all the above writes */
		dma_wmb();
		desc->die_dt = DT_FEMPTY;
	}

	*quota -= limit - (++boguscnt);

	return boguscnt <= 0;
}