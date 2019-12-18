#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rxrpc_net {int /*<<< orphan*/  conn_lock; } ;
struct TYPE_5__ {TYPE_1__* local; } ;
struct rxrpc_connection {int /*<<< orphan*/  rcu; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  cache_link; TYPE_3__* channels; TYPE_2__ params; } ;
struct TYPE_6__ {int /*<<< orphan*/  call; } ;
struct TYPE_4__ {struct rxrpc_net* rxnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_destroy_connection ; 
 int /*<<< orphan*/  rxrpc_purge_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void rxrpc_kill_connection(struct rxrpc_connection *conn)
{
	struct rxrpc_net *rxnet = conn->params.local->rxnet;

	ASSERT(!rcu_access_pointer(conn->channels[0].call) &&
	       !rcu_access_pointer(conn->channels[1].call) &&
	       !rcu_access_pointer(conn->channels[2].call) &&
	       !rcu_access_pointer(conn->channels[3].call));
	ASSERT(list_empty(&conn->cache_link));

	write_lock(&rxnet->conn_lock);
	list_del_init(&conn->proc_link);
	write_unlock(&rxnet->conn_lock);

	/* Drain the Rx queue.  Note that even though we've unpublished, an
	 * incoming packet could still be being added to our Rx queue, so we
	 * will need to drain it again in the RCU cleanup handler.
	 */
	rxrpc_purge_queue(&conn->rx_queue);

	/* Leave final destruction to RCU.  The connection processor work item
	 * must carry a ref on the connection to prevent us getting here whilst
	 * it is queued or running.
	 */
	call_rcu(&conn->rcu, rxrpc_destroy_connection);
}