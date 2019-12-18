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
typedef  int u32 ;
struct tcf_result {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_qstats; int /*<<< orphan*/  cpu_bstats; } ;
struct tcf_gact {int /*<<< orphan*/  tcf_tm; TYPE_1__ common; int /*<<< orphan*/  tcfg_ptype; int /*<<< orphan*/  tcf_action; } ;
struct tc_action {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int TC_ACT_SHOT ; 
 int /*<<< orphan*/  bstats_cpu_update (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int gact_rand (struct tcf_gact*) ; 
 int /*<<< orphan*/  qstats_drop_inc (int /*<<< orphan*/ ) ; 
 int stub1 (struct tcf_gact*) ; 
 int /*<<< orphan*/  tcf_lastuse_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ ) ; 
 struct tcf_gact* to_gact (struct tc_action const*) ; 

__attribute__((used)) static int tcf_gact_act(struct sk_buff *skb, const struct tc_action *a,
			struct tcf_result *res)
{
	struct tcf_gact *gact = to_gact(a);
	int action = READ_ONCE(gact->tcf_action);

#ifdef CONFIG_GACT_PROB
	{
	u32 ptype = READ_ONCE(gact->tcfg_ptype);

	if (ptype)
		action = gact_rand[ptype](gact);
	}
#endif
	bstats_cpu_update(this_cpu_ptr(gact->common.cpu_bstats), skb);
	if (action == TC_ACT_SHOT)
		qstats_drop_inc(this_cpu_ptr(gact->common.cpu_qstats));

	tcf_lastuse_update(&gact->tcf_tm);

	return action;
}