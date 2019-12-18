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
struct sk_buff {int dummy; } ;
struct net_dm_hw_metadata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_probe ) (struct sk_buff*,struct net_dm_hw_metadata const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  monitor_hw ; 
 size_t net_dm_alert_mode ; 
 TYPE_1__** net_dm_alert_ops_arr ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_dm_hw_metadata const*) ; 

void net_dm_hw_report(struct sk_buff *skb,
		      const struct net_dm_hw_metadata *hw_metadata)
{
	rcu_read_lock();

	if (!monitor_hw)
		goto out;

	net_dm_alert_ops_arr[net_dm_alert_mode]->hw_probe(skb, hw_metadata);

out:
	rcu_read_unlock();
}