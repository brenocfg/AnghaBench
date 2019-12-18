#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct igmpv3_query {int dummy; } ;
struct igmphdr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  group; } ;
struct TYPE_3__ {scalar_t__ daddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INADDR_ALLHOSTS_GROUP ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 TYPE_2__* igmp_hdr (struct sk_buff*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_mc_may_pull (struct sk_buff*,unsigned int) ; 
 unsigned int ip_transport_len (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static int ip_mc_check_igmp_query(struct sk_buff *skb)
{
	unsigned int transport_len = ip_transport_len(skb);
	unsigned int len;

	/* IGMPv{1,2}? */
	if (transport_len != sizeof(struct igmphdr)) {
		/* or IGMPv3? */
		if (transport_len < sizeof(struct igmpv3_query))
			return -EINVAL;

		len = skb_transport_offset(skb) + sizeof(struct igmpv3_query);
		if (!ip_mc_may_pull(skb, len))
			return -EINVAL;
	}

	/* RFC2236+RFC3376 (IGMPv2+IGMPv3) require the multicast link layer
	 * all-systems destination addresses (224.0.0.1) for general queries
	 */
	if (!igmp_hdr(skb)->group &&
	    ip_hdr(skb)->daddr != htonl(INADDR_ALLHOSTS_GROUP))
		return -EINVAL;

	return 0;
}