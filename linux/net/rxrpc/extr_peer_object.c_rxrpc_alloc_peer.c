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
struct rxrpc_peer {int cong_cwnd; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  rtt_input_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  service_conn_lock; int /*<<< orphan*/  service_conns; int /*<<< orphan*/  error_targets; int /*<<< orphan*/  local; int /*<<< orphan*/  usage; } ;
struct rxrpc_local {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int RXRPC_TX_SMSS ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_peer*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct rxrpc_peer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_get_local (struct rxrpc_local*) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct rxrpc_peer *rxrpc_alloc_peer(struct rxrpc_local *local, gfp_t gfp)
{
	struct rxrpc_peer *peer;

	_enter("");

	peer = kzalloc(sizeof(struct rxrpc_peer), gfp);
	if (peer) {
		atomic_set(&peer->usage, 1);
		peer->local = rxrpc_get_local(local);
		INIT_HLIST_HEAD(&peer->error_targets);
		peer->service_conns = RB_ROOT;
		seqlock_init(&peer->service_conn_lock);
		spin_lock_init(&peer->lock);
		spin_lock_init(&peer->rtt_input_lock);
		peer->debug_id = atomic_inc_return(&rxrpc_debug_id);

		if (RXRPC_TX_SMSS > 2190)
			peer->cong_cwnd = 2;
		else if (RXRPC_TX_SMSS > 1095)
			peer->cong_cwnd = 3;
		else
			peer->cong_cwnd = 4;
	}

	_leave(" = %p", peer);
	return peer;
}