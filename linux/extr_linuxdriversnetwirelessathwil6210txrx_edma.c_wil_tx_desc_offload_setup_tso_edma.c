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
struct TYPE_4__ {int l4_hdr_len; int cmd; int w1; int ip_length; int b11; } ;
struct TYPE_3__ {int* d; int /*<<< orphan*/  tso_mss; } ;
struct wil_tx_enhanced_desc {TYPE_2__ dma; TYPE_1__ mac; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int DMA_CFG_DESC_TX_0_L4_LENGTH_MSK ; 
 int DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_EOP_POS ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_INSERT_IP_CHKSUM_POS ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_INSERT_TCP_CHKSUM_POS ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_L4_TYPE_POS ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_PSEUDO_HEADER_CALC_EN_POS ; 
 int /*<<< orphan*/  WIL_EDMA_DESC_TX_CFG_SEG_EN_POS ; 
 int WIL_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_POS ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static void wil_tx_desc_offload_setup_tso_edma(struct wil_tx_enhanced_desc *d,
					       int tso_desc_type, bool is_ipv4,
					       int tcp_hdr_len,
					       int skb_net_hdr_len,
					       int mss)
{
	/* Number of descriptors */
	d->mac.d[2] |= 1;
	/* Maximum Segment Size */
	d->mac.tso_mss |= cpu_to_le16(mss >> 2);
	/* L4 header len: TCP header length */
	d->dma.l4_hdr_len |= tcp_hdr_len & DMA_CFG_DESC_TX_0_L4_LENGTH_MSK;
	/* EOP, TSO desc type, Segmentation enable,
	 * Insert IPv4 and TCP / UDP Checksum
	 */
	d->dma.cmd |= BIT(WIL_EDMA_DESC_TX_CFG_EOP_POS) |
		      tso_desc_type << WIL_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_POS |
		      BIT(WIL_EDMA_DESC_TX_CFG_SEG_EN_POS) |
		      BIT(WIL_EDMA_DESC_TX_CFG_INSERT_IP_CHKSUM_POS) |
		      BIT(WIL_EDMA_DESC_TX_CFG_INSERT_TCP_CHKSUM_POS);
	/* Calculate pseudo-header */
	d->dma.w1 |= BIT(WIL_EDMA_DESC_TX_CFG_PSEUDO_HEADER_CALC_EN_POS) |
		     BIT(WIL_EDMA_DESC_TX_CFG_L4_TYPE_POS);
	/* IP Header Length */
	d->dma.ip_length |= skb_net_hdr_len;
	/* MAC header length and IP address family*/
	d->dma.b11 |= ETH_HLEN |
		      is_ipv4 << DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS;
}