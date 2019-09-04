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
struct rxrpc_connection {int size_align; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  idle_timestamp; int /*<<< orphan*/  state_lock; int /*<<< orphan*/ * security; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  link; int /*<<< orphan*/  proc_link; int /*<<< orphan*/  processor; int /*<<< orphan*/  timer; int /*<<< orphan*/  waiting_calls; int /*<<< orphan*/  channel_lock; int /*<<< orphan*/  cache_link; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct rxrpc_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_connection_timer ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_no_security ; 
 int /*<<< orphan*/  rxrpc_process_connection ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct rxrpc_connection *rxrpc_alloc_connection(gfp_t gfp)
{
	struct rxrpc_connection *conn;

	_enter("");

	conn = kzalloc(sizeof(struct rxrpc_connection), gfp);
	if (conn) {
		INIT_LIST_HEAD(&conn->cache_link);
		spin_lock_init(&conn->channel_lock);
		INIT_LIST_HEAD(&conn->waiting_calls);
		timer_setup(&conn->timer, &rxrpc_connection_timer, 0);
		INIT_WORK(&conn->processor, &rxrpc_process_connection);
		INIT_LIST_HEAD(&conn->proc_link);
		INIT_LIST_HEAD(&conn->link);
		skb_queue_head_init(&conn->rx_queue);
		conn->security = &rxrpc_no_security;
		spin_lock_init(&conn->state_lock);
		conn->debug_id = atomic_inc_return(&rxrpc_debug_id);
		conn->size_align = 4;
		conn->idle_timestamp = jiffies;
	}

	_leave(" = %p{%d}", conn, conn ? conn->debug_id : 0);
	return conn;
}