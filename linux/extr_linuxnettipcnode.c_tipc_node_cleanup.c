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
struct tipc_node {int /*<<< orphan*/  delete_at; int /*<<< orphan*/  net; } ;
struct tipc_net {int /*<<< orphan*/  node_list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  node_is_up (struct tipc_node*) ; 
 int /*<<< orphan*/  spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tipc_net* tipc_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_node_clear_links (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_delete_from_list (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_write_unlock (struct tipc_node*) ; 

__attribute__((used)) static bool tipc_node_cleanup(struct tipc_node *peer)
{
	struct tipc_net *tn = tipc_net(peer->net);
	bool deleted = false;

	/* If lock held by tipc_node_stop() the node will be deleted anyway */
	if (!spin_trylock_bh(&tn->node_list_lock))
		return false;

	tipc_node_write_lock(peer);

	if (!node_is_up(peer) && time_after(jiffies, peer->delete_at)) {
		tipc_node_clear_links(peer);
		tipc_node_delete_from_list(peer);
		deleted = true;
	}
	tipc_node_write_unlock(peer);
	spin_unlock_bh(&tn->node_list_lock);
	return deleted;
}