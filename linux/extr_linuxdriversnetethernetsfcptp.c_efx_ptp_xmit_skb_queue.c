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
typedef  size_t u8 ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct efx_tx_queue {scalar_t__ timestamping; } ;
struct efx_ptp_data {TYPE_1__* channel; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
struct TYPE_2__ {struct efx_tx_queue* tx_queue; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 size_t EFX_TXQ_TYPE_OFFLOAD ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  efx_enqueue_skb (struct efx_tx_queue*,struct sk_buff*) ; 

__attribute__((used)) static void efx_ptp_xmit_skb_queue(struct efx_nic *efx, struct sk_buff *skb)
{
	struct efx_ptp_data *ptp_data = efx->ptp_data;
	struct efx_tx_queue *tx_queue;
	u8 type = skb->ip_summed == CHECKSUM_PARTIAL ? EFX_TXQ_TYPE_OFFLOAD : 0;

	tx_queue = &ptp_data->channel->tx_queue[type];
	if (tx_queue && tx_queue->timestamping) {
		efx_enqueue_skb(tx_queue, skb);
	} else {
		WARN_ONCE(1, "PTP channel has no timestamped tx queue\n");
		dev_kfree_skb_any(skb);
	}
}