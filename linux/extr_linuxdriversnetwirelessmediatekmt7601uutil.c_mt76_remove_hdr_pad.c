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

/* Variables and functions */
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

void mt76_remove_hdr_pad(struct sk_buff *skb)
{
	int len = ieee80211_get_hdrlen_from_skb(skb);

	memmove(skb->data + 2, skb->data, len);
	skb_pull(skb, 2);
}