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
struct tipc_node {int /*<<< orphan*/  net; int /*<<< orphan*/  addr; int /*<<< orphan*/  link_cnt; struct tipc_link_entry* links; } ;
struct tipc_media_addr {int dummy; } ;
struct tipc_link_entry {int /*<<< orphan*/  inputq; struct tipc_link* link; } ;
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_RESET_EVT ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __tipc_node_link_down (struct tipc_node*,int*,struct sk_buff_head*,struct tipc_media_addr**) ; 
 int /*<<< orphan*/  kfree (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_bearer_xmit (int /*<<< orphan*/ ,int,struct sk_buff_head*,struct tipc_media_addr*) ; 
 int /*<<< orphan*/  tipc_link_fsm_evt (struct tipc_link*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_link_is_establishing (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_mon_remove_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tipc_node_write_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tipc_node_link_down(struct tipc_node *n, int bearer_id, bool delete)
{
	struct tipc_link_entry *le = &n->links[bearer_id];
	struct tipc_link *l = le->link;
	struct tipc_media_addr *maddr;
	struct sk_buff_head xmitq;
	int old_bearer_id = bearer_id;

	if (!l)
		return;

	__skb_queue_head_init(&xmitq);

	tipc_node_write_lock(n);
	if (!tipc_link_is_establishing(l)) {
		__tipc_node_link_down(n, &bearer_id, &xmitq, &maddr);
		if (delete) {
			kfree(l);
			le->link = NULL;
			n->link_cnt--;
		}
	} else {
		/* Defuse pending tipc_node_link_up() */
		tipc_link_fsm_evt(l, LINK_RESET_EVT);
	}
	tipc_node_write_unlock(n);
	if (delete)
		tipc_mon_remove_peer(n->net, n->addr, old_bearer_id);
	tipc_bearer_xmit(n->net, bearer_id, &xmitq, maddr);
	tipc_sk_rcv(n->net, &le->inputq);
}