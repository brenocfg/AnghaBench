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
struct TYPE_4__ {int l3num; } ;
struct nf_conntrack_tuple {TYPE_2__ src; } ;
struct nf_conn {TYPE_1__* tuplehash; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_3__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  nf_ct_invert_tuple (struct nf_conntrack_tuple*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_nat_ipv4_manip_pkt (struct sk_buff*,int /*<<< orphan*/ ,struct nf_conntrack_tuple*,int) ; 
 int /*<<< orphan*/  nf_nat_ipv6_manip_pkt (struct sk_buff*,int /*<<< orphan*/ ,struct nf_conntrack_tuple*,int) ; 

unsigned int nf_nat_manip_pkt(struct sk_buff *skb, struct nf_conn *ct,
			      enum nf_nat_manip_type mtype,
			      enum ip_conntrack_dir dir)
{
	struct nf_conntrack_tuple target;

	/* We are aiming to look like inverse of other direction. */
	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);

	switch (target.src.l3num) {
	case NFPROTO_IPV6:
		if (nf_nat_ipv6_manip_pkt(skb, 0, &target, mtype))
			return NF_ACCEPT;
		break;
	case NFPROTO_IPV4:
		if (nf_nat_ipv4_manip_pkt(skb, 0, &target, mtype))
			return NF_ACCEPT;
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	return NF_DROP;
}