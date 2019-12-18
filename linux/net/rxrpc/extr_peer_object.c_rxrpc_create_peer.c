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
struct sockaddr_rxrpc {int dummy; } ;
struct rxrpc_sock {int dummy; } ;
struct rxrpc_peer {int /*<<< orphan*/  srx; } ;
struct rxrpc_local {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_peer*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_rxrpc*,int) ; 
 struct rxrpc_peer* rxrpc_alloc_peer (struct rxrpc_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_init_peer (struct rxrpc_sock*,struct rxrpc_peer*,unsigned long) ; 

__attribute__((used)) static struct rxrpc_peer *rxrpc_create_peer(struct rxrpc_sock *rx,
					    struct rxrpc_local *local,
					    struct sockaddr_rxrpc *srx,
					    unsigned long hash_key,
					    gfp_t gfp)
{
	struct rxrpc_peer *peer;

	_enter("");

	peer = rxrpc_alloc_peer(local, gfp);
	if (peer) {
		memcpy(&peer->srx, srx, sizeof(*srx));
		rxrpc_init_peer(rx, peer, hash_key);
	}

	_leave(" = %p", peer);
	return peer;
}