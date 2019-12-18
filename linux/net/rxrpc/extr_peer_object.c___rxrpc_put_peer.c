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
struct rxrpc_peer {TYPE_1__* local; int /*<<< orphan*/  keepalive_link; int /*<<< orphan*/  hash_link; int /*<<< orphan*/  error_targets; } ;
struct rxrpc_net {int /*<<< orphan*/  peer_hash_lock; } ;
struct TYPE_2__ {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct rxrpc_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  rxrpc_put_local (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rxrpc_put_peer(struct rxrpc_peer *peer)
{
	struct rxrpc_net *rxnet = peer->local->rxnet;

	ASSERT(hlist_empty(&peer->error_targets));

	spin_lock_bh(&rxnet->peer_hash_lock);
	hash_del_rcu(&peer->hash_link);
	list_del_init(&peer->keepalive_link);
	spin_unlock_bh(&rxnet->peer_hash_lock);

	rxrpc_put_local(peer->local);
	kfree_rcu(peer, rcu);
}