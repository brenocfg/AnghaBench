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
struct rxrpc_sock {int dummy; } ;
struct rxrpc_peer {int /*<<< orphan*/  keepalive_link; int /*<<< orphan*/  hash_link; int /*<<< orphan*/  srx; } ;
struct rxrpc_net {int /*<<< orphan*/  peer_hash_lock; int /*<<< orphan*/  peer_keepalive_new; int /*<<< orphan*/  peer_hash; } ;
struct rxrpc_local {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_init_peer (struct rxrpc_sock*,struct rxrpc_peer*,unsigned long) ; 
 unsigned long rxrpc_peer_hash_key (struct rxrpc_local*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rxrpc_new_incoming_peer(struct rxrpc_sock *rx, struct rxrpc_local *local,
			     struct rxrpc_peer *peer)
{
	struct rxrpc_net *rxnet = local->rxnet;
	unsigned long hash_key;

	hash_key = rxrpc_peer_hash_key(local, &peer->srx);
	rxrpc_init_peer(rx, peer, hash_key);

	spin_lock(&rxnet->peer_hash_lock);
	hash_add_rcu(rxnet->peer_hash, &peer->hash_link, hash_key);
	list_add_tail(&peer->keepalive_link, &rxnet->peer_keepalive_new);
	spin_unlock(&rxnet->peer_hash_lock);
}