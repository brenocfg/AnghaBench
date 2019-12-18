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
struct tcf_police_params {int dummy; } ;
struct tcf_police {int /*<<< orphan*/  params; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct tcf_police_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct tcf_police_params* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 struct tcf_police* to_police (struct tc_action*) ; 

__attribute__((used)) static void tcf_police_cleanup(struct tc_action *a)
{
	struct tcf_police *police = to_police(a);
	struct tcf_police_params *p;

	p = rcu_dereference_protected(police->params, 1);
	if (p)
		kfree_rcu(p, rcu);
}