#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct setuid_ruleset {int dummy; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  enum sid_policy_type { ____Placeholder_sid_policy_type } sid_policy_type ;

/* Variables and functions */
 int SIDPOL_DEFAULT ; 
 int _setuid_policy_lookup (struct setuid_ruleset*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct setuid_ruleset* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  safesetid_setuid_rules ; 

__attribute__((used)) static enum sid_policy_type setuid_policy_lookup(kuid_t src, kuid_t dst)
{
	enum sid_policy_type result = SIDPOL_DEFAULT;
	struct setuid_ruleset *pol;

	rcu_read_lock();
	pol = rcu_dereference(safesetid_setuid_rules);
	if (pol)
		result = _setuid_policy_lookup(pol, src, dst);
	rcu_read_unlock();
	return result;
}