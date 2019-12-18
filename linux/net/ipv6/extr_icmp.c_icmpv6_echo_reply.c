#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int /*<<< orphan*/  tmp_hdr ;
struct sock {void* sk_mark; } ;
struct sk_buff {scalar_t__ len; TYPE_6__* dev; int /*<<< orphan*/  mark; } ;
struct rt6_info {int dummy; } ;
struct TYPE_8__ {int flowlabel_reflect; scalar_t__ anycast_src_echo_reply; scalar_t__ icmpv6_echo_ignore_anycast; scalar_t__ icmpv6_echo_ignore_multicast; } ;
struct TYPE_9__ {TYPE_1__ sysctl; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6_pinfo {scalar_t__ ucast_oif; scalar_t__ mcast_oif; } ;
struct ipcm6_cookie {int /*<<< orphan*/  tclass; int /*<<< orphan*/  hlimit; } ;
struct inet6_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct icmpv6_msg {void* type; scalar_t__ offset; struct sk_buff* skb; } ;
struct icmp6hdr {void* icmp6_type; } ;
struct flowi6 {scalar_t__ flowi6_oif; struct in6_addr daddr; int /*<<< orphan*/  flowi6_uid; void* flowi6_mark; void* fl6_icmp_type; struct in6_addr saddr; int /*<<< orphan*/  flowi6_proto; int /*<<< orphan*/  flowlabel; } ;
struct dst_entry {int dummy; } ;
typedef  int /*<<< orphan*/  fl6 ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {struct in6_addr saddr; struct in6_addr daddr; } ;

/* Variables and functions */
 int FLOWLABEL_REFLECT_ICMPV6_ECHO_REPLIES ; 
 int /*<<< orphan*/  ICMP6_MIB_OUTERRORS ; 
 void* ICMPV6_ECHO_REPLY ; 
 int IFF_LOOPBACK ; 
 void* IP6_REPLY_MARK (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_ICMPV6 ; 
 scalar_t__ IS_ERR (struct dst_entry*) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  __ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* __in6_dev_get (TYPE_6__*) ; 
 struct net* dev_net (TYPE_6__*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 struct icmp6hdr* icmp6_hdr (struct sk_buff*) ; 
 scalar_t__ icmp6_iif (struct sk_buff*) ; 
 int /*<<< orphan*/  icmpv6_getfrag ; 
 int /*<<< orphan*/  icmpv6_global_allow (struct net*,void*) ; 
 int /*<<< orphan*/  icmpv6_push_pending_frames (struct sock*,struct flowi6*,struct icmp6hdr*,scalar_t__) ; 
 struct sock* icmpv6_xmit_lock (struct net*) ; 
 int /*<<< orphan*/  icmpv6_xmit_unlock (struct sock*) ; 
 int /*<<< orphan*/  icmpv6_xrlim_allow (struct sock*,void*,struct flowi6*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 scalar_t__ ip6_append_data (struct sock*,int /*<<< orphan*/ ,struct icmpv6_msg*,scalar_t__,int,struct ipcm6_cookie*,struct flowi6*,struct rt6_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ip6_dst_lookup (struct net*,struct sock*,struct dst_entry**,struct flowi6*) ; 
 int /*<<< orphan*/  ip6_flowlabel (TYPE_3__*) ; 
 int /*<<< orphan*/  ip6_flush_pending_frames (struct sock*) ; 
 int /*<<< orphan*/  ip6_sk_dst_hoplimit (struct ipv6_pinfo*,struct flowi6*,struct dst_entry*) ; 
 int /*<<< orphan*/  ipcm6_init_sk (struct ipcm6_cookie*,struct ipv6_pinfo*) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr*) ; 
 int ipv6_anycast_destination (int /*<<< orphan*/ ,struct in6_addr const*) ; 
 int /*<<< orphan*/  ipv6_get_dsfield (TYPE_3__*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memcpy (struct icmp6hdr*,struct icmp6hdr*,int) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_skb_classify_flow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 
 struct dst_entry* xfrm_lookup (struct net*,struct dst_entry*,int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icmpv6_echo_reply(struct sk_buff *skb)
{
	struct net *net = dev_net(skb->dev);
	struct sock *sk;
	struct inet6_dev *idev;
	struct ipv6_pinfo *np;
	const struct in6_addr *saddr = NULL;
	struct icmp6hdr *icmph = icmp6_hdr(skb);
	struct icmp6hdr tmp_hdr;
	struct flowi6 fl6;
	struct icmpv6_msg msg;
	struct dst_entry *dst;
	struct ipcm6_cookie ipc6;
	u32 mark = IP6_REPLY_MARK(net, skb->mark);
	bool acast;

	if (ipv6_addr_is_multicast(&ipv6_hdr(skb)->daddr) &&
	    net->ipv6.sysctl.icmpv6_echo_ignore_multicast)
		return;

	saddr = &ipv6_hdr(skb)->daddr;

	acast = ipv6_anycast_destination(skb_dst(skb), saddr);
	if (acast && net->ipv6.sysctl.icmpv6_echo_ignore_anycast)
		return;

	if (!ipv6_unicast_destination(skb) &&
	    !(net->ipv6.sysctl.anycast_src_echo_reply && acast))
		saddr = NULL;

	memcpy(&tmp_hdr, icmph, sizeof(tmp_hdr));
	tmp_hdr.icmp6_type = ICMPV6_ECHO_REPLY;

	memset(&fl6, 0, sizeof(fl6));
	if (net->ipv6.sysctl.flowlabel_reflect & FLOWLABEL_REFLECT_ICMPV6_ECHO_REPLIES)
		fl6.flowlabel = ip6_flowlabel(ipv6_hdr(skb));

	fl6.flowi6_proto = IPPROTO_ICMPV6;
	fl6.daddr = ipv6_hdr(skb)->saddr;
	if (saddr)
		fl6.saddr = *saddr;
	fl6.flowi6_oif = icmp6_iif(skb);
	fl6.fl6_icmp_type = ICMPV6_ECHO_REPLY;
	fl6.flowi6_mark = mark;
	fl6.flowi6_uid = sock_net_uid(net, NULL);
	security_skb_classify_flow(skb, flowi6_to_flowi(&fl6));

	local_bh_disable();
	sk = icmpv6_xmit_lock(net);
	if (!sk)
		goto out_bh_enable;
	sk->sk_mark = mark;
	np = inet6_sk(sk);

	if (!fl6.flowi6_oif && ipv6_addr_is_multicast(&fl6.daddr))
		fl6.flowi6_oif = np->mcast_oif;
	else if (!fl6.flowi6_oif)
		fl6.flowi6_oif = np->ucast_oif;

	if (ip6_dst_lookup(net, sk, &dst, &fl6))
		goto out;
	dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), sk, 0);
	if (IS_ERR(dst))
		goto out;

	/* Check the ratelimit */
	if ((!(skb->dev->flags & IFF_LOOPBACK) && !icmpv6_global_allow(net, ICMPV6_ECHO_REPLY)) ||
	    !icmpv6_xrlim_allow(sk, ICMPV6_ECHO_REPLY, &fl6))
		goto out_dst_release;

	idev = __in6_dev_get(skb->dev);

	msg.skb = skb;
	msg.offset = 0;
	msg.type = ICMPV6_ECHO_REPLY;

	ipcm6_init_sk(&ipc6, np);
	ipc6.hlimit = ip6_sk_dst_hoplimit(np, &fl6, dst);
	ipc6.tclass = ipv6_get_dsfield(ipv6_hdr(skb));

	if (ip6_append_data(sk, icmpv6_getfrag, &msg,
			    skb->len + sizeof(struct icmp6hdr),
			    sizeof(struct icmp6hdr), &ipc6, &fl6,
			    (struct rt6_info *)dst, MSG_DONTWAIT)) {
		__ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTERRORS);
		ip6_flush_pending_frames(sk);
	} else {
		icmpv6_push_pending_frames(sk, &fl6, &tmp_hdr,
					   skb->len + sizeof(struct icmp6hdr));
	}
out_dst_release:
	dst_release(dst);
out:
	icmpv6_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
}