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
struct sockaddr_rxrpc {int /*<<< orphan*/  transport; } ;
struct rxrpc_sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  transport; } ;
struct rxrpc_peer {int /*<<< orphan*/  usage; TYPE_1__ srx; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  keepalive_link; int /*<<< orphan*/  hash_link; } ;
struct rxrpc_net {int /*<<< orphan*/  peer_hash_lock; int /*<<< orphan*/  peer_keepalive_new; int /*<<< orphan*/  peer_hash; } ;
struct rxrpc_local {struct rxrpc_net* rxnet; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct rxrpc_peer* __rxrpc_lookup_peer_rcu (struct rxrpc_local*,struct sockaddr_rxrpc*,unsigned long) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  _net (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct rxrpc_peer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct rxrpc_peer* rxrpc_create_peer (struct rxrpc_sock*,struct rxrpc_local*,struct sockaddr_rxrpc*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_get_peer_maybe (struct rxrpc_peer*) ; 
 unsigned long rxrpc_peer_hash_key (struct rxrpc_local*,struct sockaddr_rxrpc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct rxrpc_peer *rxrpc_lookup_peer(struct rxrpc_sock *rx,
				     struct rxrpc_local *local,
				     struct sockaddr_rxrpc *srx, gfp_t gfp)
{
	struct rxrpc_peer *peer, *candidate;
	struct rxrpc_net *rxnet = local->rxnet;
	unsigned long hash_key = rxrpc_peer_hash_key(local, srx);

	_enter("{%pISp}", &srx->transport);

	/* search the peer list first */
	rcu_read_lock();
	peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
	if (peer && !rxrpc_get_peer_maybe(peer))
		peer = NULL;
	rcu_read_unlock();

	if (!peer) {
		/* The peer is not yet present in hash - create a candidate
		 * for a new record and then redo the search.
		 */
		candidate = rxrpc_create_peer(rx, local, srx, hash_key, gfp);
		if (!candidate) {
			_leave(" = NULL [nomem]");
			return NULL;
		}

		spin_lock_bh(&rxnet->peer_hash_lock);

		/* Need to check that we aren't racing with someone else */
		peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
		if (peer && !rxrpc_get_peer_maybe(peer))
			peer = NULL;
		if (!peer) {
			hash_add_rcu(rxnet->peer_hash,
				     &candidate->hash_link, hash_key);
			list_add_tail(&candidate->keepalive_link,
				      &rxnet->peer_keepalive_new);
		}

		spin_unlock_bh(&rxnet->peer_hash_lock);

		if (peer)
			kfree(candidate);
		else
			peer = candidate;
	}

	_net("PEER %d {%pISp}", peer->debug_id, &peer->srx.transport);

	_leave(" = %p {u=%d}", peer, atomic_read(&peer->usage));
	return peer;
}