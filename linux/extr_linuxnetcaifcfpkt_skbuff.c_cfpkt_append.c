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
struct sk_buff {scalar_t__ tail; scalar_t__ end; scalar_t__ len; int /*<<< orphan*/  data; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 scalar_t__ PKT_POSTFIX ; 
 scalar_t__ PKT_PREFIX ; 
 struct cfpkt* cfpkt_create (scalar_t__) ; 
 int /*<<< orphan*/  cfpkt_destroy (struct cfpkt*) ; 
 scalar_t__ is_erronous (struct cfpkt*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 struct cfpkt* skb_to_pkt (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct cfpkt *cfpkt_append(struct cfpkt *dstpkt,
			   struct cfpkt *addpkt,
			   u16 expectlen)
{
	struct sk_buff *dst = pkt_to_skb(dstpkt);
	struct sk_buff *add = pkt_to_skb(addpkt);
	u16 addlen = skb_headlen(add);
	u16 neededtailspace;
	struct sk_buff *tmp;
	u16 dstlen;
	u16 createlen;
	if (unlikely(is_erronous(dstpkt) || is_erronous(addpkt))) {
		return dstpkt;
	}
	if (expectlen > addlen)
		neededtailspace = expectlen;
	else
		neededtailspace = addlen;

	if (dst->tail + neededtailspace > dst->end) {
		/* Create a dumplicate of 'dst' with more tail space */
		struct cfpkt *tmppkt;
		dstlen = skb_headlen(dst);
		createlen = dstlen + neededtailspace;
		tmppkt = cfpkt_create(createlen + PKT_PREFIX + PKT_POSTFIX);
		if (tmppkt == NULL)
			return NULL;
		tmp = pkt_to_skb(tmppkt);
		skb_set_tail_pointer(tmp, dstlen);
		tmp->len = dstlen;
		memcpy(tmp->data, dst->data, dstlen);
		cfpkt_destroy(dstpkt);
		dst = tmp;
	}
	memcpy(skb_tail_pointer(dst), add->data, skb_headlen(add));
	cfpkt_destroy(addpkt);
	dst->tail += addlen;
	dst->len += addlen;
	return skb_to_pkt(dst);
}