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
struct team_port {int dummy; } ;
struct team {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  active_port; } ;

/* Variables and functions */
 TYPE_1__* ab_priv (struct team*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct team_port* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ team_dev_queue_xmit (struct team*,struct team_port*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ab_transmit(struct team *team, struct sk_buff *skb)
{
	struct team_port *active_port;

	active_port = rcu_dereference_bh(ab_priv(team)->active_port);
	if (unlikely(!active_port))
		goto drop;
	if (team_dev_queue_xmit(team, active_port, skb))
		return false;
	return true;

drop:
	dev_kfree_skb_any(skb);
	return false;
}