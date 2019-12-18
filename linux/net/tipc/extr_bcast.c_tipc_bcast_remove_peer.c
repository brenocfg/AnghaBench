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
struct tipc_link {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head inputq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 TYPE_1__* tipc_bc_base (struct net*) ; 
 struct tipc_link* tipc_bc_sndlink (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_calc_bc_threshold (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_select_primary (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_xmit (struct net*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_remove_bc_peer (struct tipc_link*,struct tipc_link*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_sk_rcv (struct net*,struct sk_buff_head*) ; 

void tipc_bcast_remove_peer(struct net *net, struct tipc_link *rcv_l)
{
	struct tipc_link *snd_l = tipc_bc_sndlink(net);
	struct sk_buff_head *inputq = &tipc_bc_base(net)->inputq;
	struct sk_buff_head xmitq;

	__skb_queue_head_init(&xmitq);

	tipc_bcast_lock(net);
	tipc_link_remove_bc_peer(snd_l, rcv_l, &xmitq);
	tipc_bcbase_select_primary(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);

	tipc_bcbase_xmit(net, &xmitq);

	/* Any socket wakeup messages ? */
	if (!skb_queue_empty(inputq))
		tipc_sk_rcv(net, inputq);
}