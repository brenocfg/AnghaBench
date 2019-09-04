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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct mt76x2_txwi {int dummy; } ;

/* Variables and functions */
 scalar_t__ MT_DMA_HDR_LEN ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int skb_cow (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int
mt76x2u_check_skb_rooms(struct sk_buff *skb)
{
	int hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u32 need_head;

	need_head = sizeof(struct mt76x2_txwi) + MT_DMA_HDR_LEN;
	if (hdr_len % 4)
		need_head += 2;
	return skb_cow(skb, need_head);
}