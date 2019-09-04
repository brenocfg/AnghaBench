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
struct sk_buff {scalar_t__ transport_header; scalar_t__ network_header; } ;
struct lowpan_nhc {int (* compress ) (struct sk_buff*,int /*<<< orphan*/ **) ;int /*<<< orphan*/  nexthdrlen; } ;
struct ipv6hdr {size_t nexthdr; } ;

/* Variables and functions */
 int EINVAL ; 
 struct lowpan_nhc** lowpan_nexthdr_nhcs ; 
 int /*<<< orphan*/  lowpan_nhc_lock ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct sk_buff*,int /*<<< orphan*/ **) ; 
 scalar_t__ unlikely (int) ; 

int lowpan_nhc_do_compression(struct sk_buff *skb, const struct ipv6hdr *hdr,
			      u8 **hc_ptr)
{
	int ret;
	struct lowpan_nhc *nhc;

	spin_lock_bh(&lowpan_nhc_lock);

	nhc = lowpan_nexthdr_nhcs[hdr->nexthdr];
	/* check if the nhc module was removed in unlocked part.
	 * TODO: this is a workaround we should prevent unloading
	 * of nhc modules while unlocked part, this will always drop
	 * the lowpan packet but it's very unlikely.
	 *
	 * Solution isn't easy because we need to decide at
	 * lowpan_nhc_check_compression if we do a compression or not.
	 * Because the inline data which is added to skb, we can't move this
	 * handling.
	 */
	if (unlikely(!nhc || !nhc->compress)) {
		ret = -EINVAL;
		goto out;
	}

	/* In the case of RAW sockets the transport header is not set by
	 * the ip6 stack so we must set it ourselves
	 */
	if (skb->transport_header == skb->network_header)
		skb_set_transport_header(skb, sizeof(struct ipv6hdr));

	ret = nhc->compress(skb, hc_ptr);
	if (ret < 0)
		goto out;

	/* skip the transport header */
	skb_pull(skb, nhc->nexthdrlen);

out:
	spin_unlock_bh(&lowpan_nhc_lock);

	return ret;
}