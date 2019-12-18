#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {void* ip_summed; } ;
struct mrt6msg {int im6_msgtype; int /*<<< orphan*/  im6_dst; int /*<<< orphan*/  im6_src; scalar_t__ im6_pad; int /*<<< orphan*/  im6_mif; scalar_t__ im6_mbz; } ;
struct mr_table {int /*<<< orphan*/  mroute_sk; int /*<<< orphan*/  mroute_reg_vif_num; } ;
struct ipv6hdr {int dummy; } ;
typedef  int /*<<< orphan*/  mifi_t ;
struct TYPE_3__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 void* CHECKSUM_UNNECESSARY ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MRT6MSG_WHOLEPKT ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mrt6msg_netlink_event (struct mr_table*,struct sk_buff*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*) ; 
 struct sock* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int ip6mr_cache_report(struct mr_table *mrt, struct sk_buff *pkt,
			      mifi_t mifi, int assert)
{
	struct sock *mroute6_sk;
	struct sk_buff *skb;
	struct mrt6msg *msg;
	int ret;

#ifdef CONFIG_IPV6_PIMSM_V2
	if (assert == MRT6MSG_WHOLEPKT)
		skb = skb_realloc_headroom(pkt, -skb_network_offset(pkt)
						+sizeof(*msg));
	else
#endif
		skb = alloc_skb(sizeof(struct ipv6hdr) + sizeof(*msg), GFP_ATOMIC);

	if (!skb)
		return -ENOBUFS;

	/* I suppose that internal messages
	 * do not require checksums */

	skb->ip_summed = CHECKSUM_UNNECESSARY;

#ifdef CONFIG_IPV6_PIMSM_V2
	if (assert == MRT6MSG_WHOLEPKT) {
		/* Ugly, but we have no choice with this interface.
		   Duplicate old header, fix length etc.
		   And all this only to mangle msg->im6_msgtype and
		   to set msg->im6_mbz to "mbz" :-)
		 */
		skb_push(skb, -skb_network_offset(pkt));

		skb_push(skb, sizeof(*msg));
		skb_reset_transport_header(skb);
		msg = (struct mrt6msg *)skb_transport_header(skb);
		msg->im6_mbz = 0;
		msg->im6_msgtype = MRT6MSG_WHOLEPKT;
		msg->im6_mif = mrt->mroute_reg_vif_num;
		msg->im6_pad = 0;
		msg->im6_src = ipv6_hdr(pkt)->saddr;
		msg->im6_dst = ipv6_hdr(pkt)->daddr;

		skb->ip_summed = CHECKSUM_UNNECESSARY;
	} else
#endif
	{
	/*
	 *	Copy the IP header
	 */

	skb_put(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	skb_copy_to_linear_data(skb, ipv6_hdr(pkt), sizeof(struct ipv6hdr));

	/*
	 *	Add our header
	 */
	skb_put(skb, sizeof(*msg));
	skb_reset_transport_header(skb);
	msg = (struct mrt6msg *)skb_transport_header(skb);

	msg->im6_mbz = 0;
	msg->im6_msgtype = assert;
	msg->im6_mif = mifi;
	msg->im6_pad = 0;
	msg->im6_src = ipv6_hdr(pkt)->saddr;
	msg->im6_dst = ipv6_hdr(pkt)->daddr;

	skb_dst_set(skb, dst_clone(skb_dst(pkt)));
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	rcu_read_lock();
	mroute6_sk = rcu_dereference(mrt->mroute_sk);
	if (!mroute6_sk) {
		rcu_read_unlock();
		kfree_skb(skb);
		return -EINVAL;
	}

	mrt6msg_netlink_event(mrt, skb);

	/* Deliver to user space multicast routing algorithms */
	ret = sock_queue_rcv_skb(mroute6_sk, skb);
	rcu_read_unlock();
	if (ret < 0) {
		net_warn_ratelimited("mroute6: pending queue full, dropping entries\n");
		kfree_skb(skb);
	}

	return ret;
}