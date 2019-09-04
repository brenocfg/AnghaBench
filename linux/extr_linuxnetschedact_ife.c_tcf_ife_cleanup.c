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
struct tcf_ife_params {int dummy; } ;
struct tcf_ife_info {int /*<<< orphan*/  params; int /*<<< orphan*/  tcf_lock; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tcf_ife_cleanup (struct tc_action*) ; 
 int /*<<< orphan*/  kfree_rcu (struct tcf_ife_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct tcf_ife_params* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tcf_ife_info* to_ife (struct tc_action*) ; 

__attribute__((used)) static void tcf_ife_cleanup(struct tc_action *a)
{
	struct tcf_ife_info *ife = to_ife(a);
	struct tcf_ife_params *p;

	spin_lock_bh(&ife->tcf_lock);
	_tcf_ife_cleanup(a);
	spin_unlock_bh(&ife->tcf_lock);

	p = rcu_dereference_protected(ife->params, 1);
	if (p)
		kfree_rcu(p, rcu);
}