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
typedef  int u16 ;
struct sk_buff {int len; int /*<<< orphan*/  priority; int /*<<< orphan*/  tail; int /*<<< orphan*/ * data; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 int PKT_POSTFIX ; 
 int PKT_PREFIX ; 
 struct cfpkt* cfpkt_create_pfx (int,int) ; 
 int /*<<< orphan*/  is_erronous (struct cfpkt*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int /*<<< orphan*/ * skb_tail_pointer (struct sk_buff*) ; 
 struct cfpkt* skb_to_pkt (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct cfpkt *cfpkt_split(struct cfpkt *pkt, u16 pos)
{
	struct sk_buff *skb2;
	struct sk_buff *skb = pkt_to_skb(pkt);
	struct cfpkt *tmppkt;
	u8 *split = skb->data + pos;
	u16 len2nd = skb_tail_pointer(skb) - split;

	if (unlikely(is_erronous(pkt)))
		return NULL;

	if (skb->data + pos > skb_tail_pointer(skb)) {
		PKT_ERROR(pkt, "trying to split beyond end of packet\n");
		return NULL;
	}

	/* Create a new packet for the second part of the data */
	tmppkt = cfpkt_create_pfx(len2nd + PKT_PREFIX + PKT_POSTFIX,
				  PKT_PREFIX);
	if (tmppkt == NULL)
		return NULL;
	skb2 = pkt_to_skb(tmppkt);


	if (skb2 == NULL)
		return NULL;

	/* Reduce the length of the original packet */
	skb_set_tail_pointer(skb, pos);
	skb->len = pos;

	memcpy(skb2->data, split, len2nd);
	skb2->tail += len2nd;
	skb2->len += len2nd;
	skb2->priority = skb->priority;
	return skb_to_pkt(skb2);
}