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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct in6_addr {int dummy; } ;
struct mld_msg {struct in6_addr mld_mca; } ;
struct mld2_query {scalar_t__ mld2q_nsrcs; int /*<<< orphan*/  mld2q_srcs; } ;
struct ipv6hdr {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; struct ifmcaddr6* mc_list; } ;
struct ifmcaddr6 {int mca_flags; int /*<<< orphan*/  mca_lock; int /*<<< orphan*/  mca_addr; struct ifmcaddr6* next; } ;
struct icmp6hdr {int dummy; } ;
struct TYPE_4__ {int flags; scalar_t__ ra; } ;
struct TYPE_3__ {scalar_t__ payload_len; int hop_limit; struct in6_addr const saddr; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* IP6CB (struct sk_buff*) ; 
 int IP6SKB_ROUTERALERT ; 
 int IPV6_ADDR_ANY ; 
 int IPV6_ADDR_LINKLOCAL ; 
 int IPV6_ADDR_MULTICAST ; 
 int /*<<< orphan*/  IPV6_OPT_ROUTERALERT_MLD ; 
 int MAF_GSQUERY ; 
 int MAF_TIMER_RUNNING ; 
 int MLD_V1_QUERY_LEN ; 
 int MLD_V2_QUERY_LEN_MIN ; 
 struct inet6_dev* __in6_dev_get (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ icmp6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  igmp6_group_queried (struct ifmcaddr6*,unsigned long) ; 
 int /*<<< orphan*/  ipv6_addr_equal (struct in6_addr const*,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (struct in6_addr const*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  mld_gq_start_timer (struct inet6_dev*) ; 
 scalar_t__ mld_in_v1_mode (struct inet6_dev*) ; 
 scalar_t__ mld_marksources (struct ifmcaddr6*,int,int /*<<< orphan*/ ) ; 
 int mld_process_v1 (struct inet6_dev*,struct mld_msg*,unsigned long*,int) ; 
 int mld_process_v2 (struct inet6_dev*,struct mld2_query*,unsigned long*) ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_network_header_len (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int igmp6_event_query(struct sk_buff *skb)
{
	struct mld2_query *mlh2 = NULL;
	struct ifmcaddr6 *ma;
	const struct in6_addr *group;
	unsigned long max_delay;
	struct inet6_dev *idev;
	struct mld_msg *mld;
	int group_type;
	int mark = 0;
	int len, err;

	if (!pskb_may_pull(skb, sizeof(struct in6_addr)))
		return -EINVAL;

	/* compute payload length excluding extension headers */
	len = ntohs(ipv6_hdr(skb)->payload_len) + sizeof(struct ipv6hdr);
	len -= skb_network_header_len(skb);

	/* RFC3810 6.2
	 * Upon reception of an MLD message that contains a Query, the node
	 * checks if the source address of the message is a valid link-local
	 * address, if the Hop Limit is set to 1, and if the Router Alert
	 * option is present in the Hop-By-Hop Options header of the IPv6
	 * packet.  If any of these checks fails, the packet is dropped.
	 */
	if (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL) ||
	    ipv6_hdr(skb)->hop_limit != 1 ||
	    !(IP6CB(skb)->flags & IP6SKB_ROUTERALERT) ||
	    IP6CB(skb)->ra != htons(IPV6_OPT_ROUTERALERT_MLD))
		return -EINVAL;

	idev = __in6_dev_get(skb->dev);
	if (!idev)
		return 0;

	mld = (struct mld_msg *)icmp6_hdr(skb);
	group = &mld->mld_mca;
	group_type = ipv6_addr_type(group);

	if (group_type != IPV6_ADDR_ANY &&
	    !(group_type&IPV6_ADDR_MULTICAST))
		return -EINVAL;

	if (len < MLD_V1_QUERY_LEN) {
		return -EINVAL;
	} else if (len == MLD_V1_QUERY_LEN || mld_in_v1_mode(idev)) {
		err = mld_process_v1(idev, mld, &max_delay,
				     len == MLD_V1_QUERY_LEN);
		if (err < 0)
			return err;
	} else if (len >= MLD_V2_QUERY_LEN_MIN) {
		int srcs_offset = sizeof(struct mld2_query) -
				  sizeof(struct icmp6hdr);

		if (!pskb_may_pull(skb, srcs_offset))
			return -EINVAL;

		mlh2 = (struct mld2_query *)skb_transport_header(skb);

		err = mld_process_v2(idev, mlh2, &max_delay);
		if (err < 0)
			return err;

		if (group_type == IPV6_ADDR_ANY) { /* general query */
			if (mlh2->mld2q_nsrcs)
				return -EINVAL; /* no sources allowed */

			mld_gq_start_timer(idev);
			return 0;
		}
		/* mark sources to include, if group & source-specific */
		if (mlh2->mld2q_nsrcs != 0) {
			if (!pskb_may_pull(skb, srcs_offset +
			    ntohs(mlh2->mld2q_nsrcs) * sizeof(struct in6_addr)))
				return -EINVAL;

			mlh2 = (struct mld2_query *)skb_transport_header(skb);
			mark = 1;
		}
	} else {
		return -EINVAL;
	}

	read_lock_bh(&idev->lock);
	if (group_type == IPV6_ADDR_ANY) {
		for (ma = idev->mc_list; ma; ma = ma->next) {
			spin_lock_bh(&ma->mca_lock);
			igmp6_group_queried(ma, max_delay);
			spin_unlock_bh(&ma->mca_lock);
		}
	} else {
		for (ma = idev->mc_list; ma; ma = ma->next) {
			if (!ipv6_addr_equal(group, &ma->mca_addr))
				continue;
			spin_lock_bh(&ma->mca_lock);
			if (ma->mca_flags & MAF_TIMER_RUNNING) {
				/* gsquery <- gsquery && mark */
				if (!mark)
					ma->mca_flags &= ~MAF_GSQUERY;
			} else {
				/* gsquery <- mark */
				if (mark)
					ma->mca_flags |= MAF_GSQUERY;
				else
					ma->mca_flags &= ~MAF_GSQUERY;
			}
			if (!(ma->mca_flags & MAF_GSQUERY) ||
			    mld_marksources(ma, ntohs(mlh2->mld2q_nsrcs), mlh2->mld2q_srcs))
				igmp6_group_queried(ma, max_delay);
			spin_unlock_bh(&ma->mca_lock);
			break;
		}
	}
	read_unlock_bh(&idev->lock);

	return 0;
}