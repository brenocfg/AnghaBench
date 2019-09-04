#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rtable {int dummy; } ;
struct TYPE_11__ {void* ip; } ;
struct nf_nat_range2 {int flags; int /*<<< orphan*/  max_proto; int /*<<< orphan*/  min_proto; TYPE_5__ max_addr; TYPE_5__ min_addr; } ;
struct nf_conn_nat {int /*<<< orphan*/  masq_index; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
struct net_device {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  name; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  void* __be32 ;
struct TYPE_12__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_7__ {scalar_t__ ip; } ;
struct TYPE_8__ {TYPE_1__ u3; } ;
struct TYPE_9__ {TYPE_2__ src; } ;
struct TYPE_10__ {TYPE_3__ tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 int IP_CT_NEW ; 
 int IP_CT_RELATED ; 
 int IP_CT_RELATED_REPLY ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 unsigned int NF_INET_POST_ROUTING ; 
 int /*<<< orphan*/  NF_NAT_MANIP_SRC ; 
 int NF_NAT_RANGE_MAP_IPS ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void* inet_select_addr (struct net_device const*,void*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 struct nf_conn_nat* nf_ct_nat_ext_add (struct nf_conn*) ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,struct nf_nat_range2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 void* rt_nexthop (struct rtable const*,int /*<<< orphan*/ ) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 

unsigned int
nf_nat_masquerade_ipv4(struct sk_buff *skb, unsigned int hooknum,
		       const struct nf_nat_range2 *range,
		       const struct net_device *out)
{
	struct nf_conn *ct;
	struct nf_conn_nat *nat;
	enum ip_conntrack_info ctinfo;
	struct nf_nat_range2 newrange;
	const struct rtable *rt;
	__be32 newsrc, nh;

	WARN_ON(hooknum != NF_INET_POST_ROUTING);

	ct = nf_ct_get(skb, &ctinfo);

	WARN_ON(!(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED ||
			 ctinfo == IP_CT_RELATED_REPLY)));

	/* Source address is 0.0.0.0 - locally generated packet that is
	 * probably not supposed to be masqueraded.
	 */
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip == 0)
		return NF_ACCEPT;

	rt = skb_rtable(skb);
	nh = rt_nexthop(rt, ip_hdr(skb)->daddr);
	newsrc = inet_select_addr(out, nh, RT_SCOPE_UNIVERSE);
	if (!newsrc) {
		pr_info("%s ate my IP address\n", out->name);
		return NF_DROP;
	}

	nat = nf_ct_nat_ext_add(ct);
	if (nat)
		nat->masq_index = out->ifindex;

	/* Transfer from original range. */
	memset(&newrange.min_addr, 0, sizeof(newrange.min_addr));
	memset(&newrange.max_addr, 0, sizeof(newrange.max_addr));
	newrange.flags       = range->flags | NF_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = newsrc;
	newrange.max_addr.ip = newsrc;
	newrange.min_proto   = range->min_proto;
	newrange.max_proto   = range->max_proto;

	/* Hand modified range to generic setup. */
	return nf_nat_setup_info(ct, &newrange, NF_NAT_MANIP_SRC);
}