#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_priority; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; scalar_t__ len; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  mark; int /*<<< orphan*/  priority; int /*<<< orphan*/  ignore_df; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * destructor; scalar_t__ truesize; int /*<<< orphan*/  data_len; struct sk_buff* next; } ;
struct rt6_info {int /*<<< orphan*/  rt6i_idev; int /*<<< orphan*/  dst; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
struct ipv6hdr {unsigned char nexthdr; struct in6_addr daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  hop_limit; } ;
struct ipv6_txoptions {scalar_t__ opt_nflen; scalar_t__ opt_flen; } ;
struct ipv6_pinfo {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  transmit_time; int /*<<< orphan*/  mark; scalar_t__ dst; } ;
struct flowi6 {unsigned char flowi6_proto; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowlabel; struct in6_addr daddr; } ;
struct TYPE_6__ {struct flowi6 ip6; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct inet_cork_full {TYPE_3__ base; TYPE_2__ fl; } ;
struct inet6_dev {int dummy; } ;
struct inet6_cork {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  tclass; struct ipv6_txoptions* opt; } ;
struct TYPE_10__ {int /*<<< orphan*/  icmp6_type; } ;
struct TYPE_9__ {struct sk_buff* frag_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP6MSGOUT_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_INC_STATS (struct net*,struct inet6_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICMP6_MIB_OUTMSGS ; 
 int /*<<< orphan*/  IP6_UPD_PO_STATS (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned char IPPROTO_ICMPV6 ; 
 int /*<<< orphan*/  IPSTATS_MIB_OUT ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_clone (int /*<<< orphan*/ *) ; 
 TYPE_5__* icmp6_hdr (struct sk_buff*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_autoflowlabel (struct net*,struct ipv6_pinfo*) ; 
 int /*<<< orphan*/  ip6_cork_release (struct inet_cork_full*,struct inet6_cork*) ; 
 struct inet6_dev* ip6_dst_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_flow_hdr (struct ipv6hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_make_flowlabel (struct net*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flowi6*) ; 
 int /*<<< orphan*/  ip6_sk_ignore_df (struct sock*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv6_push_frag_opts (struct sk_buff*,struct ipv6_txoptions*,unsigned char*) ; 
 int /*<<< orphan*/  ipv6_push_nfrag_opts (struct sk_buff*,struct ipv6_txoptions*,unsigned char*,struct in6_addr**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dst (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 struct net* sock_net (struct sock*) ; 

struct sk_buff *__ip6_make_skb(struct sock *sk,
			       struct sk_buff_head *queue,
			       struct inet_cork_full *cork,
			       struct inet6_cork *v6_cork)
{
	struct sk_buff *skb, *tmp_skb;
	struct sk_buff **tail_skb;
	struct in6_addr final_dst_buf, *final_dst = &final_dst_buf;
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net *net = sock_net(sk);
	struct ipv6hdr *hdr;
	struct ipv6_txoptions *opt = v6_cork->opt;
	struct rt6_info *rt = (struct rt6_info *)cork->base.dst;
	struct flowi6 *fl6 = &cork->fl.u.ip6;
	unsigned char proto = fl6->flowi6_proto;

	skb = __skb_dequeue(queue);
	if (!skb)
		goto out;
	tail_skb = &(skb_shinfo(skb)->frag_list);

	/* move skb->data to ip header from ext header */
	if (skb->data < skb_network_header(skb))
		__skb_pull(skb, skb_network_offset(skb));
	while ((tmp_skb = __skb_dequeue(queue)) != NULL) {
		__skb_pull(tmp_skb, skb_network_header_len(skb));
		*tail_skb = tmp_skb;
		tail_skb = &(tmp_skb->next);
		skb->len += tmp_skb->len;
		skb->data_len += tmp_skb->len;
		skb->truesize += tmp_skb->truesize;
		tmp_skb->destructor = NULL;
		tmp_skb->sk = NULL;
	}

	/* Allow local fragmentation. */
	skb->ignore_df = ip6_sk_ignore_df(sk);

	*final_dst = fl6->daddr;
	__skb_pull(skb, skb_network_header_len(skb));
	if (opt && opt->opt_flen)
		ipv6_push_frag_opts(skb, opt, &proto);
	if (opt && opt->opt_nflen)
		ipv6_push_nfrag_opts(skb, opt, &proto, &final_dst, &fl6->saddr);

	skb_push(skb, sizeof(struct ipv6hdr));
	skb_reset_network_header(skb);
	hdr = ipv6_hdr(skb);

	ip6_flow_hdr(hdr, v6_cork->tclass,
		     ip6_make_flowlabel(net, skb, fl6->flowlabel,
					ip6_autoflowlabel(net, np), fl6));
	hdr->hop_limit = v6_cork->hop_limit;
	hdr->nexthdr = proto;
	hdr->saddr = fl6->saddr;
	hdr->daddr = *final_dst;

	skb->priority = sk->sk_priority;
	skb->mark = cork->base.mark;

	skb->tstamp = cork->base.transmit_time;

	skb_dst_set(skb, dst_clone(&rt->dst));
	IP6_UPD_PO_STATS(net, rt->rt6i_idev, IPSTATS_MIB_OUT, skb->len);
	if (proto == IPPROTO_ICMPV6) {
		struct inet6_dev *idev = ip6_dst_idev(skb_dst(skb));

		ICMP6MSGOUT_INC_STATS(net, idev, icmp6_hdr(skb)->icmp6_type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	}

	ip6_cork_release(cork, v6_cork);
out:
	return skb;
}