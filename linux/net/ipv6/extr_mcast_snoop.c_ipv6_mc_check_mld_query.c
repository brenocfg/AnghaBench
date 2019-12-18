#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mld_msg {int /*<<< orphan*/  mld_mca; } ;
struct mld2_query {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPV6_ADDR_LINKLOCAL ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_is_ll_all_nodes (int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_mc_may_pull (struct sk_buff*,unsigned int) ; 
 unsigned int ipv6_transport_len (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int ipv6_mc_check_mld_query(struct sk_buff *skb)
{
	unsigned int transport_len = ipv6_transport_len(skb);
	struct mld_msg *mld;
	unsigned int len;

	/* RFC2710+RFC3810 (MLDv1+MLDv2) require link-local source addresses */
	if (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL))
		return -EINVAL;

	/* MLDv1? */
	if (transport_len != sizeof(struct mld_msg)) {
		/* or MLDv2? */
		if (transport_len < sizeof(struct mld2_query))
			return -EINVAL;

		len = skb_transport_offset(skb) + sizeof(struct mld2_query);
		if (!ipv6_mc_may_pull(skb, len))
			return -EINVAL;
	}

	mld = (struct mld_msg *)skb_transport_header(skb);

	/* RFC2710+RFC3810 (MLDv1+MLDv2) require the multicast link layer
	 * all-nodes destination address (ff02::1) for general queries
	 */
	if (ipv6_addr_any(&mld->mld_mca) &&
	    !ipv6_addr_is_ll_all_nodes(&ipv6_hdr(skb)->daddr))
		return -EINVAL;

	return 0;
}