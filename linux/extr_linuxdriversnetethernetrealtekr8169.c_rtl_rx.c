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
typedef  int u32 ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {int bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  packets; } ;
struct rtl8169_private {unsigned int cur_rx; scalar_t__ mac_version; TYPE_2__ rx_stats; int /*<<< orphan*/  napi; int /*<<< orphan*/ * Rx_databuff; struct RxDesc* RxDescArray; } ;
struct TYPE_3__ {int /*<<< orphan*/  multicast; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {int features; TYPE_1__ stats; } ;
struct RxDesc {scalar_t__ opts2; int /*<<< orphan*/  addr; int /*<<< orphan*/  opts1; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DescOwn ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 unsigned int NUM_RX_DESC ; 
 scalar_t__ PACKET_MULTICAST ; 
 int /*<<< orphan*/  RTL_FLAG_TASK_RESET_PENDING ; 
 scalar_t__ RTL_GIGA_MAC_VER_01 ; 
 int RxCRC ; 
 int RxFOVF ; 
 int RxRES ; 
 int RxRUNT ; 
 int RxRWT ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (int,unsigned int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_info (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int rtl8169_fragmented_frame (int) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (struct RxDesc*) ; 
 int /*<<< orphan*/  rtl8169_rx_csum (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rtl8169_rx_vlan_tag (struct RxDesc*,struct sk_buff*) ; 
 struct sk_buff* rtl8169_try_rx_copy (int /*<<< orphan*/ ,struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_schedule_task (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_err ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rtl_rx(struct net_device *dev, struct rtl8169_private *tp, u32 budget)
{
	unsigned int cur_rx, rx_left;
	unsigned int count;

	cur_rx = tp->cur_rx;

	for (rx_left = min(budget, NUM_RX_DESC); rx_left > 0; rx_left--, cur_rx++) {
		unsigned int entry = cur_rx % NUM_RX_DESC;
		struct RxDesc *desc = tp->RxDescArray + entry;
		u32 status;

		status = le32_to_cpu(desc->opts1);
		if (status & DescOwn)
			break;

		/* This barrier is needed to keep us from reading
		 * any other fields out of the Rx descriptor until
		 * we know the status of DescOwn
		 */
		dma_rmb();

		if (unlikely(status & RxRES)) {
			netif_info(tp, rx_err, dev, "Rx ERROR. status = %08x\n",
				   status);
			dev->stats.rx_errors++;
			if (status & (RxRWT | RxRUNT))
				dev->stats.rx_length_errors++;
			if (status & RxCRC)
				dev->stats.rx_crc_errors++;
			/* RxFOVF is a reserved bit on later chip versions */
			if (tp->mac_version == RTL_GIGA_MAC_VER_01 &&
			    status & RxFOVF) {
				rtl_schedule_task(tp, RTL_FLAG_TASK_RESET_PENDING);
				dev->stats.rx_fifo_errors++;
			} else if (status & (RxRUNT | RxCRC) &&
				   !(status & RxRWT) &&
				   dev->features & NETIF_F_RXALL) {
				goto process_pkt;
			}
		} else {
			struct sk_buff *skb;
			dma_addr_t addr;
			int pkt_size;

process_pkt:
			addr = le64_to_cpu(desc->addr);
			if (likely(!(dev->features & NETIF_F_RXFCS)))
				pkt_size = (status & 0x00003fff) - 4;
			else
				pkt_size = status & 0x00003fff;

			/*
			 * The driver does not support incoming fragmented
			 * frames. They are seen as a symptom of over-mtu
			 * sized frames.
			 */
			if (unlikely(rtl8169_fragmented_frame(status))) {
				dev->stats.rx_dropped++;
				dev->stats.rx_length_errors++;
				goto release_descriptor;
			}

			skb = rtl8169_try_rx_copy(tp->Rx_databuff[entry],
						  tp, pkt_size, addr);
			if (!skb) {
				dev->stats.rx_dropped++;
				goto release_descriptor;
			}

			rtl8169_rx_csum(skb, status);
			skb_put(skb, pkt_size);
			skb->protocol = eth_type_trans(skb, dev);

			rtl8169_rx_vlan_tag(desc, skb);

			if (skb->pkt_type == PACKET_MULTICAST)
				dev->stats.multicast++;

			napi_gro_receive(&tp->napi, skb);

			u64_stats_update_begin(&tp->rx_stats.syncp);
			tp->rx_stats.packets++;
			tp->rx_stats.bytes += pkt_size;
			u64_stats_update_end(&tp->rx_stats.syncp);
		}
release_descriptor:
		desc->opts2 = 0;
		rtl8169_mark_to_asic(desc);
	}

	count = cur_rx - tp->cur_rx;
	tp->cur_rx = cur_rx;

	return count;
}