#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key; int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; } ;
struct nft_flow_rule {TYPE_2__ match; TYPE_3__* rule; } ;
struct TYPE_4__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; } ;
struct TYPE_6__ {TYPE_1__ match; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_3__* flow_rule_alloc (int) ; 
 int /*<<< orphan*/  kfree (struct nft_flow_rule*) ; 
 struct nft_flow_rule* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nft_flow_rule *nft_flow_rule_alloc(int num_actions)
{
	struct nft_flow_rule *flow;

	flow = kzalloc(sizeof(struct nft_flow_rule), GFP_KERNEL);
	if (!flow)
		return NULL;

	flow->rule = flow_rule_alloc(num_actions);
	if (!flow->rule) {
		kfree(flow);
		return NULL;
	}

	flow->rule->match.dissector	= &flow->match.dissector;
	flow->rule->match.mask		= &flow->match.mask;
	flow->rule->match.key		= &flow->match.key;

	return flow;
}