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
struct sk_buff {int dummy; } ;
struct cfpkt {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  PKT_ERROR (struct cfpkt*,char*) ; 
 scalar_t__ PKT_LEN_WHEN_EXTENDING ; 
 int is_erronous (struct cfpkt*) ; 
 scalar_t__ likely (void const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,scalar_t__) ; 
 struct sk_buff* pkt_to_skb (struct cfpkt*) ; 
 int /*<<< orphan*/ * pskb_put (struct sk_buff*,struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 scalar_t__ skb_cow_data (struct sk_buff*,scalar_t__,struct sk_buff**) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int cfpkt_add_body(struct cfpkt *pkt, const void *data, u16 len)
{
	struct sk_buff *skb = pkt_to_skb(pkt);
	struct sk_buff *lastskb;
	u8 *to;
	u16 addlen = 0;


	if (unlikely(is_erronous(pkt)))
		return -EPROTO;

	lastskb = skb;

	/* Check whether we need to add space at the tail */
	if (unlikely(skb_tailroom(skb) < len)) {
		if (likely(len < PKT_LEN_WHEN_EXTENDING))
			addlen = PKT_LEN_WHEN_EXTENDING;
		else
			addlen = len;
	}

	/* Check whether we need to change the SKB before writing to the tail */
	if (unlikely((addlen > 0) || skb_cloned(skb) || skb_shared(skb))) {

		/* Make sure data is writable */
		if (unlikely(skb_cow_data(skb, addlen, &lastskb) < 0)) {
			PKT_ERROR(pkt, "cow failed\n");
			return -EPROTO;
		}
	}

	/* All set to put the last SKB and optionally write data there. */
	to = pskb_put(skb, lastskb, len);
	if (likely(data))
		memcpy(to, data, len);
	return 0;
}