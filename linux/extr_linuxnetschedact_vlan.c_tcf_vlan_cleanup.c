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
struct tcf_vlan_params {int dummy; } ;
struct tcf_vlan {int /*<<< orphan*/  vlan_p; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct tcf_vlan_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct tcf_vlan_params* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 struct tcf_vlan* to_vlan (struct tc_action*) ; 

__attribute__((used)) static void tcf_vlan_cleanup(struct tc_action *a)
{
	struct tcf_vlan *v = to_vlan(a);
	struct tcf_vlan_params *p;

	p = rcu_dereference_protected(v->vlan_p, 1);
	if (p)
		kfree_rcu(p, rcu);
}