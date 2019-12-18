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
struct tcf_ct_params {int /*<<< orphan*/  rcu; } ;
struct tcf_ct {int /*<<< orphan*/  params; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcf_ct_params* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcf_ct_params_free ; 
 struct tcf_ct* to_ct (struct tc_action*) ; 

__attribute__((used)) static void tcf_ct_cleanup(struct tc_action *a)
{
	struct tcf_ct_params *params;
	struct tcf_ct *c = to_ct(a);

	params = rcu_dereference_protected(c->params, 1);
	if (params)
		call_rcu(&params->rcu, tcf_ct_params_free);
}