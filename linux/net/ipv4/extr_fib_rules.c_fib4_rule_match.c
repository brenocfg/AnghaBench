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
struct flowi4 {int daddr; int saddr; scalar_t__ flowi4_tos; scalar_t__ flowi4_proto; int /*<<< orphan*/  fl4_dport; int /*<<< orphan*/  fl4_sport; } ;
struct TYPE_2__ {struct flowi4 ip4; } ;
struct flowi {TYPE_1__ u; } ;
struct fib_rule {scalar_t__ ip_proto; int /*<<< orphan*/  dport_range; int /*<<< orphan*/  sport_range; } ;
struct fib4_rule {int src; int srcmask; int dst; int dstmask; scalar_t__ tos; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  fib_rule_port_inrange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fib_rule_port_range_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib4_rule_match(struct fib_rule *rule, struct flowi *fl, int flags)
{
	struct fib4_rule *r = (struct fib4_rule *) rule;
	struct flowi4 *fl4 = &fl->u.ip4;
	__be32 daddr = fl4->daddr;
	__be32 saddr = fl4->saddr;

	if (((saddr ^ r->src) & r->srcmask) ||
	    ((daddr ^ r->dst) & r->dstmask))
		return 0;

	if (r->tos && (r->tos != fl4->flowi4_tos))
		return 0;

	if (rule->ip_proto && (rule->ip_proto != fl4->flowi4_proto))
		return 0;

	if (fib_rule_port_range_set(&rule->sport_range) &&
	    !fib_rule_port_inrange(&rule->sport_range, fl4->fl4_sport))
		return 0;

	if (fib_rule_port_range_set(&rule->dport_range) &&
	    !fib_rule_port_inrange(&rule->dport_range, fl4->fl4_dport))
		return 0;

	return 1;
}