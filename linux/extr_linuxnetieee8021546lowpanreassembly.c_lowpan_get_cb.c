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
typedef  scalar_t__ u8 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct lowpan_802154_cb {int d_size; scalar_t__ d_offset; int /*<<< orphan*/  d_tag; } ;
struct ipv6hdr {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ LOWPAN_DISPATCH_FRAGN ; 
 scalar_t__ LOWPAN_FRAG_DGRAM_SIZE_HIGH_MASK ; 
 scalar_t__ LOWPAN_FRAG_DGRAM_SIZE_HIGH_SHIFT ; 
 int lowpan_fetch_skb (struct sk_buff*,scalar_t__*,int) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lowpan_get_cb(struct sk_buff *skb, u8 frag_type,
			 struct lowpan_802154_cb *cb)
{
	bool fail;
	u8 high = 0, low = 0;
	__be16 d_tag = 0;

	fail = lowpan_fetch_skb(skb, &high, 1);
	fail |= lowpan_fetch_skb(skb, &low, 1);
	/* remove the dispatch value and use first three bits as high value
	 * for the datagram size
	 */
	cb->d_size = (high & LOWPAN_FRAG_DGRAM_SIZE_HIGH_MASK) <<
		LOWPAN_FRAG_DGRAM_SIZE_HIGH_SHIFT | low;
	fail |= lowpan_fetch_skb(skb, &d_tag, 2);
	cb->d_tag = ntohs(d_tag);

	if (frag_type == LOWPAN_DISPATCH_FRAGN) {
		fail |= lowpan_fetch_skb(skb, &cb->d_offset, 1);
	} else {
		skb_reset_network_header(skb);
		cb->d_offset = 0;
		/* check if datagram_size has ipv6hdr on FRAG1 */
		fail |= cb->d_size < sizeof(struct ipv6hdr);
		/* check if we can dereference the dispatch value */
		fail |= !skb->len;
	}

	if (unlikely(fail))
		return -EIO;

	return 0;
}