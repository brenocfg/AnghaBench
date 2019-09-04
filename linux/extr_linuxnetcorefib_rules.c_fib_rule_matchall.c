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
struct TYPE_3__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fib_rule {int suppress_ifgroup; int suppress_prefixlen; int /*<<< orphan*/  dport_range; int /*<<< orphan*/  sport_range; TYPE_1__ uid_range; scalar_t__ flags; scalar_t__ tun_id; scalar_t__ mark; scalar_t__ oifindex; scalar_t__ iifindex; } ;
struct TYPE_4__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 TYPE_2__ fib_kuid_range_unset ; 
 scalar_t__ fib_rule_port_range_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool fib_rule_matchall(const struct fib_rule *rule)
{
	if (rule->iifindex || rule->oifindex || rule->mark || rule->tun_id ||
	    rule->flags)
		return false;
	if (rule->suppress_ifgroup != -1 || rule->suppress_prefixlen != -1)
		return false;
	if (!uid_eq(rule->uid_range.start, fib_kuid_range_unset.start) ||
	    !uid_eq(rule->uid_range.end, fib_kuid_range_unset.end))
		return false;
	if (fib_rule_port_range_set(&rule->sport_range))
		return false;
	if (fib_rule_port_range_set(&rule->dport_range))
		return false;
	return true;
}