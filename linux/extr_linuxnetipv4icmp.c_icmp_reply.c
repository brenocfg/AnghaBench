#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct sock {void* sk_mark; } ;
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  mark; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct rtable {TYPE_1__ dst; } ;
struct net {int dummy; } ;
struct ipcm_cookie {TYPE_4__* opt; void* addr; } ;
struct inet_sock {int /*<<< orphan*/  tos; } ;
struct TYPE_13__ {void* faddr; scalar_t__ srr; scalar_t__ optlen; } ;
struct TYPE_11__ {TYPE_6__ opt; } ;
struct TYPE_12__ {TYPE_4__ opt; } ;
struct TYPE_9__ {int type; int code; scalar_t__ checksum; } ;
struct TYPE_10__ {TYPE_2__ icmph; } ;
struct icmp_bxm {TYPE_5__ replyopts; TYPE_3__ data; } ;
struct flowi4 {int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  flowi4_proto; int /*<<< orphan*/  flowi4_tos; int /*<<< orphan*/  flowi4_uid; void* flowi4_mark; void* saddr; void* daddr; } ;
typedef  int /*<<< orphan*/  fl4 ;
typedef  void* __be32 ;
struct TYPE_14__ {int /*<<< orphan*/  tos; void* saddr; } ;

/* Variables and functions */
 void* IP4_REPLY_MARK (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_ICMP ; 
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  RT_TOS (int /*<<< orphan*/ ) ; 
 struct net* dev_net (int /*<<< orphan*/ ) ; 
 void* fib_compute_spec_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  flowi4_to_flowi (struct flowi4*) ; 
 int /*<<< orphan*/  icmp_push_reply (struct icmp_bxm*,struct flowi4*,struct ipcm_cookie*,struct rtable**) ; 
 struct sock* icmp_xmit_lock (struct net*) ; 
 int /*<<< orphan*/  icmp_xmit_unlock (struct sock*) ; 
 int /*<<< orphan*/  icmpv4_global_allow (struct net*,int,int) ; 
 scalar_t__ icmpv4_xrlim_allow (struct net*,struct rtable*,struct flowi4*,int,int) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 TYPE_7__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_options_echo (struct net*,TYPE_6__*,struct sk_buff*) ; 
 struct rtable* ip_route_output_key (struct net*,struct flowi4*) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  ipcm_init (struct ipcm_cookie*) ; 
 int /*<<< orphan*/  l3mdev_master_ifindex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_skb_classify_flow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icmp_reply(struct icmp_bxm *icmp_param, struct sk_buff *skb)
{
	struct ipcm_cookie ipc;
	struct rtable *rt = skb_rtable(skb);
	struct net *net = dev_net(rt->dst.dev);
	struct flowi4 fl4;
	struct sock *sk;
	struct inet_sock *inet;
	__be32 daddr, saddr;
	u32 mark = IP4_REPLY_MARK(net, skb->mark);
	int type = icmp_param->data.icmph.type;
	int code = icmp_param->data.icmph.code;

	if (ip_options_echo(net, &icmp_param->replyopts.opt.opt, skb))
		return;

	/* Needed by both icmp_global_allow and icmp_xmit_lock */
	local_bh_disable();

	/* global icmp_msgs_per_sec */
	if (!icmpv4_global_allow(net, type, code))
		goto out_bh_enable;

	sk = icmp_xmit_lock(net);
	if (!sk)
		goto out_bh_enable;
	inet = inet_sk(sk);

	icmp_param->data.icmph.checksum = 0;

	ipcm_init(&ipc);
	inet->tos = ip_hdr(skb)->tos;
	sk->sk_mark = mark;
	daddr = ipc.addr = ip_hdr(skb)->saddr;
	saddr = fib_compute_spec_dst(skb);

	if (icmp_param->replyopts.opt.opt.optlen) {
		ipc.opt = &icmp_param->replyopts.opt;
		if (ipc.opt->opt.srr)
			daddr = icmp_param->replyopts.opt.opt.faddr;
	}
	memset(&fl4, 0, sizeof(fl4));
	fl4.daddr = daddr;
	fl4.saddr = saddr;
	fl4.flowi4_mark = mark;
	fl4.flowi4_uid = sock_net_uid(net, NULL);
	fl4.flowi4_tos = RT_TOS(ip_hdr(skb)->tos);
	fl4.flowi4_proto = IPPROTO_ICMP;
	fl4.flowi4_oif = l3mdev_master_ifindex(skb->dev);
	security_skb_classify_flow(skb, flowi4_to_flowi(&fl4));
	rt = ip_route_output_key(net, &fl4);
	if (IS_ERR(rt))
		goto out_unlock;
	if (icmpv4_xrlim_allow(net, rt, &fl4, type, code))
		icmp_push_reply(icmp_param, &fl4, &ipc, &rt);
	ip_rt_put(rt);
out_unlock:
	icmp_xmit_unlock(sk);
out_bh_enable:
	local_bh_enable();
}