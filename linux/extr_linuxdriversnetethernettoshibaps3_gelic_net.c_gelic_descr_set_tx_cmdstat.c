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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ protocol; } ;
struct gelic_descr {void* dmac_cmd_status; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int GELIC_DESCR_DMA_CMD_NO_CHKSUM ; 
 int GELIC_DESCR_DMA_CMD_TCP_CHKSUM ; 
 int GELIC_DESCR_DMA_CMD_UDP_CHKSUM ; 
 int GELIC_DESCR_TX_DMA_FRAME_TAIL ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static void gelic_descr_set_tx_cmdstat(struct gelic_descr *descr,
				       struct sk_buff *skb)
{
	if (skb->ip_summed != CHECKSUM_PARTIAL)
		descr->dmac_cmd_status =
			cpu_to_be32(GELIC_DESCR_DMA_CMD_NO_CHKSUM |
				    GELIC_DESCR_TX_DMA_FRAME_TAIL);
	else {
		/* is packet ip?
		 * if yes: tcp? udp? */
		if (skb->protocol == htons(ETH_P_IP)) {
			if (ip_hdr(skb)->protocol == IPPROTO_TCP)
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_TCP_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);

			else if (ip_hdr(skb)->protocol == IPPROTO_UDP)
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_UDP_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);
			else	/*
				 * the stack should checksum non-tcp and non-udp
				 * packets on his own: NETIF_F_IP_CSUM
				 */
				descr->dmac_cmd_status =
				cpu_to_be32(GELIC_DESCR_DMA_CMD_NO_CHKSUM |
					    GELIC_DESCR_TX_DMA_FRAME_TAIL);
		}
	}
}