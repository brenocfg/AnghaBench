#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct nf_nat_l4proto {int dummy; } ;
struct nf_nat_l3proto {int /*<<< orphan*/  (* manip_pkt ) (struct sk_buff*,int /*<<< orphan*/ ,struct nf_nat_l4proto const*,struct nf_conntrack_tuple*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  protonum; } ;
struct TYPE_6__ {int /*<<< orphan*/  l3num; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; TYPE_3__ src; } ;
struct nf_conn {TYPE_2__* tuplehash; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_5__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 struct nf_nat_l3proto* __nf_nat_l3proto_find (int /*<<< orphan*/ ) ; 
 struct nf_nat_l4proto* __nf_nat_l4proto_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_invert_tuplepr (struct nf_conntrack_tuple*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ,struct nf_nat_l4proto const*,struct nf_conntrack_tuple*,int) ; 

__attribute__((used)) static unsigned int nf_nat_manip_pkt(struct sk_buff *skb, struct nf_conn *ct,
				     enum nf_nat_manip_type mtype,
				     enum ip_conntrack_dir dir)
{
	const struct nf_nat_l3proto *l3proto;
	const struct nf_nat_l4proto *l4proto;
	struct nf_conntrack_tuple target;

	/* We are aiming to look like inverse of other direction. */
	nf_ct_invert_tuplepr(&target, &ct->tuplehash[!dir].tuple);

	l3proto = __nf_nat_l3proto_find(target.src.l3num);
	l4proto = __nf_nat_l4proto_find(target.src.l3num,
					target.dst.protonum);
	if (!l3proto->manip_pkt(skb, 0, l4proto, &target, mtype))
		return NF_DROP;

	return NF_ACCEPT;
}