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
struct xt_action_param {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ip_set_adt_opt {scalar_t__ dim; scalar_t__ family; int cmdflags; } ;
struct ip_set {scalar_t__ family; TYPE_2__* type; int /*<<< orphan*/  lock; TYPE_1__* variant; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;
struct TYPE_4__ {scalar_t__ dimension; int features; } ;
struct TYPE_3__ {int (* kadt ) (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,int /*<<< orphan*/ ,struct ip_set_adt_opt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  IPSET_ADD ; 
 int IPSET_FLAG_RETURN_NOMATCH ; 
 int /*<<< orphan*/  IPSET_TEST ; 
 int IPSET_TYPE_NOMATCH ; 
 scalar_t__ NFPROTO_UNSPEC ; 
 struct ip_set* ip_set_rcu_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,int /*<<< orphan*/ ,struct ip_set_adt_opt*) ; 
 int stub2 (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,int /*<<< orphan*/ ,struct ip_set_adt_opt*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param const*) ; 

int
ip_set_test(ip_set_id_t index, const struct sk_buff *skb,
	    const struct xt_action_param *par, struct ip_set_adt_opt *opt)
{
	struct ip_set *set = ip_set_rcu_get(xt_net(par), index);
	int ret = 0;

	BUG_ON(!set);
	pr_debug("set %s, index %u\n", set->name, index);

	if (opt->dim < set->type->dimension ||
	    !(opt->family == set->family || set->family == NFPROTO_UNSPEC))
		return 0;

	rcu_read_lock_bh();
	ret = set->variant->kadt(set, skb, par, IPSET_TEST, opt);
	rcu_read_unlock_bh();

	if (ret == -EAGAIN) {
		/* Type requests element to be completed */
		pr_debug("element must be completed, ADD is triggered\n");
		spin_lock_bh(&set->lock);
		set->variant->kadt(set, skb, par, IPSET_ADD, opt);
		spin_unlock_bh(&set->lock);
		ret = 1;
	} else {
		/* --return-nomatch: invert matched element */
		if ((opt->cmdflags & IPSET_FLAG_RETURN_NOMATCH) &&
		    (set->type->features & IPSET_TYPE_NOMATCH) &&
		    (ret > 0 || ret == -ENOTEMPTY))
			ret = -ret;
	}

	/* Convert error codes to nomatch */
	return (ret < 0 ? 0 : ret);
}