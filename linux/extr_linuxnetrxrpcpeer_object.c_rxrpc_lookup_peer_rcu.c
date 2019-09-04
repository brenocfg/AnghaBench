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
struct sockaddr_rxrpc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  transport; } ;
struct rxrpc_peer {int /*<<< orphan*/  usage; TYPE_1__ srx; int /*<<< orphan*/  debug_id; } ;
struct rxrpc_local {int dummy; } ;

/* Variables and functions */
 struct rxrpc_peer* __rxrpc_lookup_peer_rcu (struct rxrpc_local*,struct sockaddr_rxrpc const*,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_peer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _net (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long rxrpc_peer_hash_key (struct rxrpc_local*,struct sockaddr_rxrpc const*) ; 

struct rxrpc_peer *rxrpc_lookup_peer_rcu(struct rxrpc_local *local,
					 const struct sockaddr_rxrpc *srx)
{
	struct rxrpc_peer *peer;
	unsigned long hash_key = rxrpc_peer_hash_key(local, srx);

	peer = __rxrpc_lookup_peer_rcu(local, srx, hash_key);
	if (peer) {
		_net("PEER %d {%pISp}", peer->debug_id, &peer->srx.transport);
		_leave(" = %p {u=%d}", peer, atomic_read(&peer->usage));
	}
	return peer;
}