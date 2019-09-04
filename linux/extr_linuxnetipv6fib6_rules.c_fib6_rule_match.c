#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct flowi6 {scalar_t__ flowi6_proto; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_5__ {struct flowi6 ip6; } ;
struct flowi {TYPE_1__ u; } ;
struct fib_rule {scalar_t__ ip_proto; int /*<<< orphan*/  dport_range; int /*<<< orphan*/  sport_range; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {scalar_t__ plen; int /*<<< orphan*/  addr; } ;
struct fib6_rule {scalar_t__ tclass; TYPE_4__ common; TYPE_3__ src; TYPE_2__ dst; } ;

/* Variables and functions */
 int FIB_RULE_FIND_SADDR ; 
 int RT6_LOOKUP_F_HAS_SADDR ; 
 int /*<<< orphan*/  fib_rule_port_inrange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fib_rule_port_range_set (int /*<<< orphan*/ *) ; 
 scalar_t__ ip6_tclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_prefix_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int fib6_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct fib6_rule *r = (struct fib6_rule *) rule;
	struct flowi6 *fl6 = &fl->u.ip6;

	if (r->dst.plen &&
	    !ipv6_prefix_equal(&fl6->daddr, &r->dst.addr, r->dst.plen))
		return 0;

	/*
	 * If FIB_RULE_FIND_SADDR is set and we do not have a
	 * source address for the traffic, we defer check for
	 * source address.
	 */
	if (r->src.plen) {
		if (flags & RT6_LOOKUP_F_HAS_SADDR) {
			if (!ipv6_prefix_equal(&fl6->saddr, &r->src.addr,
					       r->src.plen))
				return 0;
		} else if (!(r->common.flags & FIB_RULE_FIND_SADDR))
			return 0;
	}

	if (r->tclass && r->tclass != ip6_tclass(fl6->flowlabel))
		return 0;

	if (rule->ip_proto && (rule->ip_proto != fl6->flowi6_proto))
		return 0;

	if (fib_rule_port_range_set(&rule->sport_range) &&
	    !fib_rule_port_inrange(&rule->sport_range, fl6->fl6_sport))
		return 0;

	if (fib_rule_port_range_set(&rule->dport_range) &&
	    !fib_rule_port_inrange(&rule->dport_range, fl6->fl6_dport))
		return 0;

	return 1;
}