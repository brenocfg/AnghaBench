#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockcm_cookie {int /*<<< orphan*/  tsflags; int /*<<< orphan*/  transmit_time; int /*<<< orphan*/  mark; } ;
struct sock {int /*<<< orphan*/  sk_priority; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  network_header; int /*<<< orphan*/  transport_header; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; int /*<<< orphan*/  protocol; } ;
struct TYPE_4__ {TYPE_2__* dev; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_idev; TYPE_1__ dst; } ;
struct net {int dummy; } ;
struct msghdr {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_pinfo {int /*<<< orphan*/  recverr; } ;
struct flowi6 {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_5__ {int needed_tailroom; int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int EFAULT ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IP6_INC_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUTDISCARDS ; 
 int LL_RESERVED_SPACE (TYPE_2__*) ; 
 unsigned int MSG_CONFIRM ; 
 unsigned int MSG_DONTWAIT ; 
 unsigned int MSG_PROBE ; 
 int /*<<< orphan*/  NFPROTO_IPV6 ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,struct sock*,struct sk_buff*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_LOCAL_OUT ; 
 int /*<<< orphan*/  dst_output ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_local_error (struct sock*,int,struct flowi6*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* l3mdev_ip6_out (struct sock*,struct sk_buff*) ; 
 int memcpy_from_msg (struct ipv6hdr*,struct msghdr*,int) ; 
 int net_xmit_errno (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,TYPE_1__*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_dst_pending_confirm (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_setup_tx_timestamp (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,int,unsigned int,int*) ; 
 struct net* sock_net (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rawv6_send_hdrinc(struct sock *sk, struct msghdr *msg, int length,
			struct flowi6 *fl6, struct dst_entry **dstp,
			unsigned int flags, const struct sockcm_cookie *sockc)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net *net = sock_net(sk);
	struct ipv6hdr *iph;
	struct sk_buff *skb;
	int err;
	struct rt6_info *rt = (struct rt6_info *)*dstp;
	int hlen = LL_RESERVED_SPACE(rt->dst.dev);
	int tlen = rt->dst.dev->needed_tailroom;

	if (length > rt->dst.dev->mtu) {
		ipv6_local_error(sk, EMSGSIZE, fl6, rt->dst.dev->mtu);
		return -EMSGSIZE;
	}
	if (length < sizeof(struct ipv6hdr))
		return -EINVAL;
	if (flags&MSG_PROBE)
		goto out;

	skb = sock_alloc_send_skb(sk,
				  length + hlen + tlen + 15,
				  flags & MSG_DONTWAIT, &err);
	if (!skb)
		goto error;
	skb_reserve(skb, hlen);

	skb->protocol = htons(ETH_P_IPV6);
	skb->priority = sk->sk_priority;
	skb->mark = sockc->mark;
	skb->tstamp = sockc->transmit_time;

	skb_put(skb, length);
	skb_reset_network_header(skb);
	iph = ipv6_hdr(skb);

	skb->ip_summed = CHECKSUM_NONE;

	skb_setup_tx_timestamp(skb, sockc->tsflags);

	if (flags & MSG_CONFIRM)
		skb_set_dst_pending_confirm(skb, 1);

	skb->transport_header = skb->network_header;
	err = memcpy_from_msg(iph, msg, length);
	if (err) {
		err = -EFAULT;
		kfree_skb(skb);
		goto error;
	}

	skb_dst_set(skb, &rt->dst);
	*dstp = NULL;

	/* if egress device is enslaved to an L3 master device pass the
	 * skb to its handler for processing
	 */
	skb = l3mdev_ip6_out(sk, skb);
	if (unlikely(!skb))
		return 0;

	/* Acquire rcu_read_lock() in case we need to use rt->rt6i_idev
	 * in the error path. Since skb has been freed, the dst could
	 * have been queued for deletion.
	 */
	rcu_read_lock();
	IP6_UPD_PO_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT, net, sk, skb,
		      NULL, rt->dst.dev, dst_output);
	if (err > 0)
		err = net_xmit_errno(err);
	if (err) {
		IP6_INC_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
		rcu_read_unlock();
		goto error_check;
	}
	rcu_read_unlock();
out:
	return 0;

error:
	IP6_INC_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUTDISCARDS);
error_check:
	if (err == -ENOBUFS && !np->recverr)
		err = 0;
	return err;
}