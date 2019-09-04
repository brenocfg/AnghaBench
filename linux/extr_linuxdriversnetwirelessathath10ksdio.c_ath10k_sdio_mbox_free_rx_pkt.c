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
struct ath10k_sdio_rx_data {int trailer_only; scalar_t__ act_len; scalar_t__ alloc_len; int /*<<< orphan*/ * skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ath10k_sdio_mbox_free_rx_pkt(struct ath10k_sdio_rx_data *pkt)
{
	dev_kfree_skb(pkt->skb);
	pkt->skb = NULL;
	pkt->alloc_len = 0;
	pkt->act_len = 0;
	pkt->trailer_only = false;
}