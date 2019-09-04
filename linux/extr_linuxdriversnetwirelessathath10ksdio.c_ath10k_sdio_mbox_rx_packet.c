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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ath10k_sdio_rx_data {int status; int /*<<< orphan*/  act_len; int /*<<< orphan*/  alloc_len; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  htc_addr; } ;
struct ath10k_sdio {TYPE_1__ mbox_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int ath10k_sdio_readsb (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_sdio_mbox_rx_packet(struct ath10k *ar,
				      struct ath10k_sdio_rx_data *pkt)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sk_buff *skb = pkt->skb;
	int ret;

	ret = ath10k_sdio_readsb(ar, ar_sdio->mbox_info.htc_addr,
				 skb->data, pkt->alloc_len);
	pkt->status = ret;
	if (!ret)
		skb_put(skb, pkt->act_len);

	return ret;
}