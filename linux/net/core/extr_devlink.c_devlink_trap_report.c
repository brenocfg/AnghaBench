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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_dm_hw_metadata {int dummy; } ;
struct devlink_trap_item {TYPE_1__* group_item; int /*<<< orphan*/  stats; } ;
struct devlink_port {int dummy; } ;
struct devlink {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_trap_report_metadata_fill (struct net_dm_hw_metadata*,struct devlink_trap_item*,struct devlink_port*) ; 
 int /*<<< orphan*/  devlink_trap_stats_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_dm_hw_report (struct sk_buff*,struct net_dm_hw_metadata*) ; 

void devlink_trap_report(struct devlink *devlink, struct sk_buff *skb,
			 void *trap_ctx, struct devlink_port *in_devlink_port)
{
	struct devlink_trap_item *trap_item = trap_ctx;
	struct net_dm_hw_metadata hw_metadata = {};

	devlink_trap_stats_update(trap_item->stats, skb->len);
	devlink_trap_stats_update(trap_item->group_item->stats, skb->len);

	devlink_trap_report_metadata_fill(&hw_metadata, trap_item,
					  in_devlink_port);
	net_dm_hw_report(skb, &hw_metadata);
}