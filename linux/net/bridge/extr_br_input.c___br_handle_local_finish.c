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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_bridge_port {int flags; int /*<<< orphan*/  br; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROPT_NO_LL_LEARN ; 
 int BR_LEARNING ; 
 int /*<<< orphan*/  br_fdb_update (int /*<<< orphan*/ ,struct net_bridge_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_opt_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_bridge_port* br_port_get_rcu (int /*<<< orphan*/ ) ; 
 scalar_t__ br_should_learn (struct net_bridge_port*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 

__attribute__((used)) static void __br_handle_local_finish(struct sk_buff *skb)
{
	struct net_bridge_port *p = br_port_get_rcu(skb->dev);
	u16 vid = 0;

	/* check if vlan is allowed, to avoid spoofing */
	if ((p->flags & BR_LEARNING) &&
	    !br_opt_get(p->br, BROPT_NO_LL_LEARN) &&
	    br_should_learn(p, skb, &vid))
		br_fdb_update(p->br, p, eth_hdr(skb)->h_source, vid, false);
}