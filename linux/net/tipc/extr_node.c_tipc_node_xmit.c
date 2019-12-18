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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_node {int* active_links; struct tipc_link_entry* links; } ;
struct tipc_link_entry {int /*<<< orphan*/  maddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  link; } ;
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int ENOBUFS ; 
 int INVALID_BEARER_ID ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 scalar_t__ in_own_node (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_bearer_xmit (struct net*,int,struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int tipc_link_xmit (int /*<<< orphan*/ ,struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_loopback_trace (struct net*,struct sk_buff_head*) ; 
 struct tipc_node* tipc_node_find (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_link_down (struct tipc_node*,int,int) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (struct net*,struct sk_buff_head*) ; 
 scalar_t__ unlikely (int) ; 

int tipc_node_xmit(struct net *net, struct sk_buff_head *list,
		   u32 dnode, int selector)
{
	struct tipc_link_entry *le = NULL;
	struct tipc_node *n;
	struct sk_buff_head xmitq;
	int bearer_id;
	int rc;

	if (in_own_node(net, dnode)) {
		tipc_loopback_trace(net, list);
		spin_lock_init(&list->lock);
		tipc_sk_rcv(net, list);
		return 0;
	}

	n = tipc_node_find(net, dnode);
	if (unlikely(!n)) {
		__skb_queue_purge(list);
		return -EHOSTUNREACH;
	}

	tipc_node_read_lock(n);
	bearer_id = n->active_links[selector & 1];
	if (unlikely(bearer_id == INVALID_BEARER_ID)) {
		tipc_node_read_unlock(n);
		tipc_node_put(n);
		__skb_queue_purge(list);
		return -EHOSTUNREACH;
	}

	__skb_queue_head_init(&xmitq);
	le = &n->links[bearer_id];
	spin_lock_bh(&le->lock);
	rc = tipc_link_xmit(le->link, list, &xmitq);
	spin_unlock_bh(&le->lock);
	tipc_node_read_unlock(n);

	if (unlikely(rc == -ENOBUFS))
		tipc_node_link_down(n, bearer_id, false);
	else
		tipc_bearer_xmit(net, bearer_id, &xmitq, &le->maddr);

	tipc_node_put(n);

	return rc;
}