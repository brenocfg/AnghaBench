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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 int is_erronous (struct cfpkt*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_pull (struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int cfpkt_extr_head(struct cfpkt *pkt, void *data, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	u8 *from;
	if (unlikely(is_erronous(pkt)))
		return -EPROTO;

	if (unlikely(len > skb->len)) {
		PKT_ERROR(pkt, "read beyond end of packet\n");
		return -EPROTO;
	}

	if (unlikely(len > skb_headlen(skb))) {
		if (unlikely(skb_linearize(skb) != 0)) {
			PKT_ERROR(pkt, "linearize failed\n");
			return -EPROTO;
		}
	}
	from = skb_pull(skb, len);
	from -= len;
	if (data)
		memcpy(data, from, len);
	return 0;
}