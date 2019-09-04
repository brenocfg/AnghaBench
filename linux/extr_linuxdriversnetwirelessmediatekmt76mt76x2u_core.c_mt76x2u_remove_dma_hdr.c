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
struct sk_buff {scalar_t__ data; } ;
struct mt76x2_txwi {int dummy; } ;

/* Variables and functions */
 int MT_DMA_HDR_LEN ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void mt76x2u_remove_dma_hdr(struct sk_buff *skb)
{
	int hdr_len;

	skb_pull(skb, sizeof(struct mt76x2_txwi) + MT_DMA_HDR_LEN);
	hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	if (hdr_len % 4) {
		memmove(skb->data + 2, skb->data, hdr_len);
		skb_pull(skb, 2);
	}
}