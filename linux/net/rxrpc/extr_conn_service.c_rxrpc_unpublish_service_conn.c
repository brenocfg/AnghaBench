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
struct rxrpc_peer {int /*<<< orphan*/  service_conn_lock; int /*<<< orphan*/  service_conns; } ;
struct TYPE_2__ {struct rxrpc_peer* peer; } ;
struct rxrpc_connection {int /*<<< orphan*/  service_node; int /*<<< orphan*/  flags; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXRPC_CONN_IN_SERVICE_CONNS ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock_bh (int /*<<< orphan*/ *) ; 

void rxrpc_unpublish_service_conn(struct rxrpc_connection *conn)
{
	struct rxrpc_peer *peer = conn->params.peer;

	write_seqlock_bh(&peer->service_conn_lock);
	if (test_and_clear_bit(RXRPC_CONN_IN_SERVICE_CONNS, &conn->flags))
		rb_erase(&conn->service_node, &peer->service_conns);
	write_sequnlock_bh(&peer->service_conn_lock);
}