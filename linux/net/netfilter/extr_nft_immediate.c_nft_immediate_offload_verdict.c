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
struct nft_offload_ctx {int /*<<< orphan*/  num_actions; } ;
struct TYPE_6__ {int code; } ;
struct nft_data {TYPE_3__ verdict; } ;
struct nft_immediate_expr {struct nft_data data; } ;
struct nft_flow_rule {TYPE_2__* rule; } ;
struct flow_action_entry {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {struct flow_action_entry* entries; } ;
struct TYPE_5__ {TYPE_1__ action; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FLOW_ACTION_ACCEPT ; 
 int /*<<< orphan*/  FLOW_ACTION_DROP ; 
#define  NF_ACCEPT 129 
#define  NF_DROP 128 

__attribute__((used)) static int nft_immediate_offload_verdict(struct nft_offload_ctx *ctx,
					 struct nft_flow_rule *flow,
					 const struct nft_immediate_expr *priv)
{
	struct flow_action_entry *entry;
	const struct nft_data *data;

	entry = &flow->rule->action.entries[ctx->num_actions++];

	data = &priv->data;
	switch (data->verdict.code) {
	case NF_ACCEPT:
		entry->id = FLOW_ACTION_ACCEPT;
		break;
	case NF_DROP:
		entry->id = FLOW_ACTION_DROP;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}