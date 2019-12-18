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
struct tipc_node {scalar_t__ sync_point; } ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_FAILOVER_BEGIN_EVT ; 
 int /*<<< orphan*/  LINK_SYNCH_END_EVT ; 
 int /*<<< orphan*/  NODE_FAILOVER_BEGIN_EVT ; 
 int /*<<< orphan*/  NODE_SYNCH_END_EVT ; 
 int U16_MAX ; 
 int /*<<< orphan*/  tipc_link_failover_prepare (struct tipc_link*,struct tipc_link*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_is_reset (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_is_up (struct tipc_link*) ; 
 scalar_t__ tipc_link_rcv_nxt (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_node_fsm_evt (struct tipc_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tipc_node_link_failover(struct tipc_node *n, struct tipc_link *l,
				    struct tipc_link *tnl,
				    struct sk_buff_head *xmitq)
{
	/* Avoid to be "self-failover" that can never end */
	if (!tipc_link_is_up(tnl))
		return;

	/* Don't rush, failure link may be in the process of resetting */
	if (l && !tipc_link_is_reset(l))
		return;

	tipc_link_fsm_evt(tnl, LINK_SYNCH_END_EVT);
	tipc_node_fsm_evt(n, NODE_SYNCH_END_EVT);

	n->sync_point = tipc_link_rcv_nxt(tnl) + (U16_MAX / 2 - 1);
	tipc_link_failover_prepare(l, tnl, xmitq);

	if (l)
		tipc_link_fsm_evt(l, LINK_FAILOVER_BEGIN_EVT);
	tipc_node_fsm_evt(n, NODE_FAILOVER_BEGIN_EVT);
}