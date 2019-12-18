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
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct tipc_node {TYPE_2__* links; TYPE_1__ bc_entry; int /*<<< orphan*/  net; } ;
struct tipc_msg {int dummy; } ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct TYPE_4__ {struct tipc_link* link; } ;

/* Variables and functions */
 int TIPC_LINK_DOWN_EVT ; 
 int TIPC_LINK_SND_STATE ; 
 scalar_t__ msg_probe (struct tipc_msg*) ; 
 int tipc_bcast_sync_rcv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tipc_msg*) ; 
 int /*<<< orphan*/  tipc_link_build_state_msg (struct tipc_link*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_node_read_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_reset_links (struct tipc_node*) ; 

__attribute__((used)) static void tipc_node_bc_sync_rcv(struct tipc_node *n, struct tipc_msg *hdr,
				  int bearer_id, struct sk_buff_head *xmitq)
{
	struct tipc_link *ucl;
	int rc;

	rc = tipc_bcast_sync_rcv(n->net, n->bc_entry.link, hdr);

	if (rc & TIPC_LINK_DOWN_EVT) {
		tipc_node_reset_links(n);
		return;
	}

	if (!(rc & TIPC_LINK_SND_STATE))
		return;

	/* If probe message, a STATE response will be sent anyway */
	if (msg_probe(hdr))
		return;

	/* Produce a STATE message carrying broadcast NACK */
	tipc_node_read_lock(n);
	ucl = n->links[bearer_id].link;
	if (ucl)
		tipc_link_build_state_msg(ucl, xmitq);
	tipc_node_read_unlock(n);
}