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
typedef  int /*<<< orphan*/  tc_action_priv_destructor ;
struct tcf_sample {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  psample_group; } ;
struct tc_action {int dummy; } ;
struct psample_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psample_group_take (struct psample_group*) ; 
 struct psample_group* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_psample_group_put ; 
 struct tcf_sample* to_sample (struct tc_action const*) ; 

__attribute__((used)) static struct psample_group *
tcf_sample_get_group(const struct tc_action *a,
		     tc_action_priv_destructor *destructor)
{
	struct tcf_sample *s = to_sample(a);
	struct psample_group *group;

	spin_lock_bh(&s->tcf_lock);
	group = rcu_dereference_protected(s->psample_group,
					  lockdep_is_held(&s->tcf_lock));
	if (group) {
		psample_group_take(group);
		*destructor = tcf_psample_group_put;
	}
	spin_unlock_bh(&s->tcf_lock);

	return group;
}