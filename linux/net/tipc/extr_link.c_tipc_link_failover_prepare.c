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
struct sk_buff_head {int dummy; } ;
struct tipc_link {int drop_point; int /*<<< orphan*/ * failover_reasm_skb; struct sk_buff_head failover_deferdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_create_dummy_tnl_msg (struct tipc_link*,struct sk_buff_head*) ; 
 scalar_t__ unlikely (int) ; 

void tipc_link_failover_prepare(struct tipc_link *l, struct tipc_link *tnl,
				struct sk_buff_head *xmitq)
{
	struct sk_buff_head *fdefq = &tnl->failover_deferdq;

	tipc_link_create_dummy_tnl_msg(tnl, xmitq);

	/* This failover link enpoint was never established before,
	 * so it has not received anything from peer.
	 * Otherwise, it must be a normal failover situation or the
	 * node has entered SELF_DOWN_PEER_LEAVING and both peer nodes
	 * would have to start over from scratch instead.
	 */
	tnl->drop_point = 1;
	tnl->failover_reasm_skb = NULL;

	/* Initiate the link's failover deferdq */
	if (unlikely(!skb_queue_empty(fdefq))) {
		pr_warn("Link failover deferdq not empty: %d!\n",
			skb_queue_len(fdefq));
		__skb_queue_purge(fdefq);
	}
}