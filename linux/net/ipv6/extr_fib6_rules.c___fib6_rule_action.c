#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int error; } ;
struct rt6_info {TYPE_4__ dst; } ;
struct TYPE_7__ {struct rt6_info* ip6_null_entry; struct rt6_info* ip6_prohibit_entry; struct rt6_info* ip6_blk_hole_entry; } ;
struct net {TYPE_2__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct TYPE_6__ {struct flowi6 ip6; } ;
struct flowi {TYPE_1__ u; } ;
struct fib_rule {int action; struct net* fr_net; } ;
struct fib_lookup_arg {int /*<<< orphan*/  lookup_data; struct rt6_info* (* lookup_ptr ) (struct net*,struct fib6_table*,struct flowi6*,int /*<<< orphan*/ ,int) ;struct fib6_result* result; } ;
struct fib6_table {int dummy; } ;
struct fib6_result {struct rt6_info* rt6; } ;
typedef  struct rt6_info* (* pol_lookup_t ) (struct net*,struct fib6_table*,struct flowi6*,int /*<<< orphan*/ ,int) ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENETUNREACH ; 
#define  FR_ACT_BLACKHOLE 131 
#define  FR_ACT_PROHIBIT 130 
#define  FR_ACT_TO_TBL 129 
#define  FR_ACT_UNREACHABLE 128 
 int RT6_LOOKUP_F_DST_NOREF ; 
 int /*<<< orphan*/  dst_hold (TYPE_4__*) ; 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int fib6_rule_saddr (struct net*,struct fib_rule*,int,struct flowi6*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib_rule_get_table (struct fib_rule*,struct fib_lookup_arg*) ; 
 TYPE_3__* ip6_dst_idev (TYPE_4__*) ; 
 int /*<<< orphan*/  ip6_rt_put_flags (struct rt6_info*,int) ; 

__attribute__((used)) static int __fib6_rule_action(struct fib_rule *rule, struct flowi *flp,
			      int flags, struct fib_lookup_arg *arg)
{
	struct fib6_result *res = arg->result;
	struct flowi6 *flp6 = &flp->u.ip6;
	struct rt6_info *rt = NULL;
	struct fib6_table *table;
	struct net *net = rule->fr_net;
	pol_lookup_t lookup = arg->lookup_ptr;
	int err = 0;
	u32 tb_id;

	switch (rule->action) {
	case FR_ACT_TO_TBL:
		break;
	case FR_ACT_UNREACHABLE:
		err = -ENETUNREACH;
		rt = net->ipv6.ip6_null_entry;
		goto discard_pkt;
	default:
	case FR_ACT_BLACKHOLE:
		err = -EINVAL;
		rt = net->ipv6.ip6_blk_hole_entry;
		goto discard_pkt;
	case FR_ACT_PROHIBIT:
		err = -EACCES;
		rt = net->ipv6.ip6_prohibit_entry;
		goto discard_pkt;
	}

	tb_id = fib_rule_get_table(rule, arg);
	table = fib6_get_table(net, tb_id);
	if (!table) {
		err = -EAGAIN;
		goto out;
	}

	rt = lookup(net, table, flp6, arg->lookup_data, flags);
	if (rt != net->ipv6.ip6_null_entry) {
		err = fib6_rule_saddr(net, rule, flags, flp6,
				      ip6_dst_idev(&rt->dst)->dev);

		if (err == -EAGAIN)
			goto again;

		err = rt->dst.error;
		if (err != -EAGAIN)
			goto out;
	}
again:
	ip6_rt_put_flags(rt, flags);
	err = -EAGAIN;
	rt = NULL;
	goto out;

discard_pkt:
	if (!(flags & RT6_LOOKUP_F_DST_NOREF))
		dst_hold(&rt->dst);
out:
	res->rt6 = rt;
	return err;
}