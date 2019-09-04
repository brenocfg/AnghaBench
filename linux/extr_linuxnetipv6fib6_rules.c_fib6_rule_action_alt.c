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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct fib6_info* fib6_null_entry; } ;
struct net {TYPE_1__ ipv6; } ;
struct flowi6 {int dummy; } ;
struct TYPE_4__ {struct flowi6 ip6; } ;
struct flowi {TYPE_2__ u; } ;
struct fib_rule {int action; struct net* fr_net; } ;
struct fib_lookup_arg {struct fib6_info* result; scalar_t__ lookup_data; } ;
struct fib6_table {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENETUNREACH ; 
#define  FR_ACT_BLACKHOLE 131 
#define  FR_ACT_PROHIBIT 130 
#define  FR_ACT_TO_TBL 129 
#define  FR_ACT_UNREACHABLE 128 
 struct fib6_table* fib6_get_table (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fib6_info_nh_dev (struct fib6_info*) ; 
 int fib6_rule_saddr (struct net*,struct fib_rule*,int,struct flowi6*,int /*<<< orphan*/ ) ; 
 struct fib6_info* fib6_table_lookup (struct net*,struct fib6_table*,int,struct flowi6*,int) ; 
 int /*<<< orphan*/  fib_rule_get_table (struct fib_rule*,struct fib_lookup_arg*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int fib6_rule_action_alt(struct fib_rule *rule, struct flowi *flp,
				int flags, struct fib_lookup_arg *arg)
{
	struct flowi6 *flp6 = &flp->u.ip6;
	struct net *net = rule->fr_net;
	struct fib6_table *table;
	struct fib6_info *f6i;
	int err = -EAGAIN, *oif;
	u32 tb_id;

	switch (rule->action) {
	case FR_ACT_TO_TBL:
		break;
	case FR_ACT_UNREACHABLE:
		return -ENETUNREACH;
	case FR_ACT_PROHIBIT:
		return -EACCES;
	case FR_ACT_BLACKHOLE:
	default:
		return -EINVAL;
	}

	tb_id = fib_rule_get_table(rule, arg);
	table = fib6_get_table(net, tb_id);
	if (!table)
		return -EAGAIN;

	oif = (int *)arg->lookup_data;
	f6i = fib6_table_lookup(net, table, *oif, flp6, flags);
	if (f6i != net->ipv6.fib6_null_entry) {
		err = fib6_rule_saddr(net, rule, flags, flp6,
				      fib6_info_nh_dev(f6i));

		if (likely(!err))
			arg->result = f6i;
	}

	return err;
}