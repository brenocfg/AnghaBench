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
struct tcf_chain {scalar_t__ action_refcnt; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTM_DELCHAIN ; 
 int /*<<< orphan*/  tc_chain_notify (struct tcf_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tc_chain_tmplt_del (struct tcf_chain*) ; 
 int /*<<< orphan*/  tcf_chain_destroy (struct tcf_chain*) ; 

__attribute__((used)) static void __tcf_chain_put(struct tcf_chain *chain, bool by_act)
{
	if (by_act)
		chain->action_refcnt--;
	chain->refcnt--;

	/* The last dropped non-action reference will trigger notification. */
	if (chain->refcnt - chain->action_refcnt == 0 && !by_act)
		tc_chain_notify(chain, NULL, 0, 0, RTM_DELCHAIN, false);

	if (chain->refcnt == 0) {
		tc_chain_tmplt_del(chain);
		tcf_chain_destroy(chain);
	}
}