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
struct rxrpc_net {int kill_all_client_conns; int /*<<< orphan*/  client_conn_reaper; int /*<<< orphan*/  client_conn_reap_timer; int /*<<< orphan*/  client_conn_cache_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _debug (char*) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_queue_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rxrpc_destroy_all_client_connections(struct rxrpc_net *rxnet)
{
	_enter("");

	spin_lock(&rxnet->client_conn_cache_lock);
	rxnet->kill_all_client_conns = true;
	spin_unlock(&rxnet->client_conn_cache_lock);

	del_timer_sync(&rxnet->client_conn_reap_timer);

	if (!rxrpc_queue_work(&rxnet->client_conn_reaper))
		_debug("destroy: queue failed");

	_leave("");
}