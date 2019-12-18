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
struct rpc_xprt {int /*<<< orphan*/  xprt_net; int /*<<< orphan*/  backlog; int /*<<< orphan*/  sending; int /*<<< orphan*/  pending; int /*<<< orphan*/  binding; scalar_t__ bind_index; int /*<<< orphan*/  cwnd; int /*<<< orphan*/  last_used; int /*<<< orphan*/  xprt_switch; int /*<<< orphan*/  bc_pa_list; int /*<<< orphan*/  bc_pa_lock; int /*<<< orphan*/  xmit_queue; int /*<<< orphan*/  recv_queue; int /*<<< orphan*/  free; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  reserve_lock; int /*<<< orphan*/  transport_lock; int /*<<< orphan*/  kref; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RPC_INITCWND ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_init_priority_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_init_xid (struct rpc_xprt*) ; 

__attribute__((used)) static void xprt_init(struct rpc_xprt *xprt, struct net *net)
{
	kref_init(&xprt->kref);

	spin_lock_init(&xprt->transport_lock);
	spin_lock_init(&xprt->reserve_lock);
	spin_lock_init(&xprt->queue_lock);

	INIT_LIST_HEAD(&xprt->free);
	xprt->recv_queue = RB_ROOT;
	INIT_LIST_HEAD(&xprt->xmit_queue);
#if defined(CONFIG_SUNRPC_BACKCHANNEL)
	spin_lock_init(&xprt->bc_pa_lock);
	INIT_LIST_HEAD(&xprt->bc_pa_list);
#endif /* CONFIG_SUNRPC_BACKCHANNEL */
	INIT_LIST_HEAD(&xprt->xprt_switch);

	xprt->last_used = jiffies;
	xprt->cwnd = RPC_INITCWND;
	xprt->bind_index = 0;

	rpc_init_wait_queue(&xprt->binding, "xprt_binding");
	rpc_init_wait_queue(&xprt->pending, "xprt_pending");
	rpc_init_wait_queue(&xprt->sending, "xprt_sending");
	rpc_init_priority_wait_queue(&xprt->backlog, "xprt_backlog");

	xprt_init_xid(xprt);

	xprt->xprt_net = get_net(net);
}