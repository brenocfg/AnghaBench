#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  protonum; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; } ;
struct nf_conntrack_l4proto {int dummy; } ;

/* Variables and functions */
 int ctnetlink_dump_tuples_ip (struct sk_buff*,struct nf_conntrack_tuple const*) ; 
 int ctnetlink_dump_tuples_proto (struct sk_buff*,struct nf_conntrack_tuple const*,struct nf_conntrack_l4proto const*) ; 
 struct nf_conntrack_l4proto* nf_ct_l4proto_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int ctnetlink_dump_tuples(struct sk_buff *skb,
				 const struct nf_conntrack_tuple *tuple)
{
	const struct nf_conntrack_l4proto *l4proto;
	int ret;

	rcu_read_lock();
	ret = ctnetlink_dump_tuples_ip(skb, tuple);

	if (ret >= 0) {
		l4proto = nf_ct_l4proto_find(tuple->dst.protonum);
		ret = ctnetlink_dump_tuples_proto(skb, tuple, l4proto);
	}
	rcu_read_unlock();
	return ret;
}