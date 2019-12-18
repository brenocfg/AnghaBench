#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nft_offload_ctx {int /*<<< orphan*/  num_actions; int /*<<< orphan*/  net; } ;
struct nft_flow_rule {TYPE_2__* rule; } ;
struct net_device {int dummy; } ;
struct flow_action_entry {int id; struct net_device* dev; } ;
typedef  enum flow_action_id { ____Placeholder_flow_action_id } flow_action_id ;
struct TYPE_3__ {struct flow_action_entry* entries; } ;
struct TYPE_4__ {TYPE_1__ action; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int) ; 

int nft_fwd_dup_netdev_offload(struct nft_offload_ctx *ctx,
			       struct nft_flow_rule *flow,
			       enum flow_action_id id, int oif)
{
	struct flow_action_entry *entry;
	struct net_device *dev;

	/* nft_flow_rule_destroy() releases the reference on this device. */
	dev = dev_get_by_index(ctx->net, oif);
	if (!dev)
		return -EOPNOTSUPP;

	entry = &flow->rule->action.entries[ctx->num_actions++];
	entry->id = id;
	entry->dev = dev;

	return 0;
}