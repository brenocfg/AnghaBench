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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int data_len; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 int /*<<< orphan*/  ___pskb_trim (struct sk_buff*,scalar_t__) ; 
 int cfpkt_getlen (struct cfpkt*) ; 
 int /*<<< orphan*/  cfpkt_pad_trail (struct cfpkt*,scalar_t__) ; 
 int is_erronous (struct cfpkt*) ; 
 scalar_t__ likely (int) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int cfpkt_setlen(struct cfpkt *pkt, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);


	if (unlikely(is_erronous(pkt)))
		return -EPROTO;

	if (likely(len <= skb->len)) {
		if (unlikely(skb->data_len))
			___pskb_trim(skb, len);
		else
			skb_trim(skb, len);

		return cfpkt_getlen(pkt);
	}

	/* Need to expand SKB */
	if (unlikely(!cfpkt_pad_trail(pkt, len - skb->len)))
		PKT_ERROR(pkt, "skb_pad_trail failed\n");

	return cfpkt_getlen(pkt);
}