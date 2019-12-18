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
struct rxrpc_net {int dummy; } ;
struct TYPE_2__ {scalar_t__ srx_service; } ;
struct rxrpc_local {int /*<<< orphan*/  debug_id; TYPE_1__ srx; int /*<<< orphan*/  services_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  client_conns_lock; int /*<<< orphan*/  client_conns; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  reject_queue; int /*<<< orphan*/  defrag_sem; int /*<<< orphan*/  processor; int /*<<< orphan*/  link; struct rxrpc_net* rxnet; int /*<<< orphan*/  active_users; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  _leave (char*,struct rxrpc_local*) ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct rxrpc_local* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct sockaddr_rxrpc const*,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_debug_id ; 
 int /*<<< orphan*/  rxrpc_local_new ; 
 int /*<<< orphan*/  rxrpc_local_processor ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_rxrpc_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rxrpc_local *rxrpc_alloc_local(struct rxrpc_net *rxnet,
					     const struct sockaddr_rxrpc *srx)
{
	struct rxrpc_local *local;

	local = kzalloc(sizeof(struct rxrpc_local), GFP_KERNEL);
	if (local) {
		atomic_set(&local->usage, 1);
		atomic_set(&local->active_users, 1);
		local->rxnet = rxnet;
		INIT_LIST_HEAD(&local->link);
		INIT_WORK(&local->processor, rxrpc_local_processor);
		init_rwsem(&local->defrag_sem);
		skb_queue_head_init(&local->reject_queue);
		skb_queue_head_init(&local->event_queue);
		local->client_conns = RB_ROOT;
		spin_lock_init(&local->client_conns_lock);
		spin_lock_init(&local->lock);
		rwlock_init(&local->services_lock);
		local->debug_id = atomic_inc_return(&rxrpc_debug_id);
		memcpy(&local->srx, srx, sizeof(*srx));
		local->srx.srx_service = 0;
		trace_rxrpc_local(local->debug_id, rxrpc_local_new, 1, NULL);
	}

	_leave(" = %p", local);
	return local;
}