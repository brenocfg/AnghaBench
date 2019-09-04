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
struct TYPE_3__ {scalar_t__ tun_id; } ;
struct flowi {scalar_t__ flowi_iif; scalar_t__ flowi_oif; int flowi_mark; int /*<<< orphan*/  flowi_uid; TYPE_1__ flowi_tun_key; } ;
struct fib_rules_ops {int (* match ) (struct fib_rule*,struct flowi*,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fib_rule {scalar_t__ iifindex; scalar_t__ oifindex; int mark; int mark_mask; scalar_t__ tun_id; int flags; TYPE_2__ uid_range; int /*<<< orphan*/  fr_net; scalar_t__ l3mdev; } ;
struct fib_lookup_arg {int dummy; } ;

/* Variables and functions */
 int FIB_RULE_INVERT ; 
 int /*<<< orphan*/  l3mdev_fib_rule_match (int /*<<< orphan*/ ,struct flowi*,struct fib_lookup_arg*) ; 
 int stub1 (struct fib_rule*,struct flowi*,int) ; 
 scalar_t__ uid_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fib_rule_match(struct fib_rule *rule, struct fib_rules_ops *ops,
			  struct flowi *fl, int flags,
			  struct fib_lookup_arg *arg)
{
	int ret = 0;

	if (rule->iifindex && (rule->iifindex != fl->flowi_iif))
		goto out;

	if (rule->oifindex && (rule->oifindex != fl->flowi_oif))
		goto out;

	if ((rule->mark ^ fl->flowi_mark) & rule->mark_mask)
		goto out;

	if (rule->tun_id && (rule->tun_id != fl->flowi_tun_key.tun_id))
		goto out;

	if (rule->l3mdev && !l3mdev_fib_rule_match(rule->fr_net, fl, arg))
		goto out;

	if (uid_lt(fl->flowi_uid, rule->uid_range.start) ||
	    uid_gt(fl->flowi_uid, rule->uid_range.end))
		goto out;

	ret = ops->match(rule, fl, flags);
out:
	return (rule->flags & FIB_RULE_INVERT) ? !ret : ret;
}