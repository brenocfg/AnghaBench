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
typedef  scalar_t__ u16 ;
struct tipc_link {int bc_peer_is_up; void* state; int /*<<< orphan*/  ackers; scalar_t__ snd_nxt; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 void* LINK_ESTABLISHED ; 
 void* LINK_RESET ; 
 int /*<<< orphan*/  TIPC_DUMP_ALL ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_bc_ack_rcv (struct tipc_link*,scalar_t__,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_link_reset (struct tipc_link*) ; 
 int /*<<< orphan*/  trace_tipc_link_reset (struct tipc_link*,int /*<<< orphan*/ ,char*) ; 

void tipc_link_remove_bc_peer(struct tipc_link *snd_l,
			      struct tipc_link *rcv_l,
			      struct sk_buff_head *xmitq)
{
	u16 ack = snd_l->snd_nxt - 1;

	snd_l->ackers--;
	rcv_l->bc_peer_is_up = true;
	rcv_l->state = LINK_ESTABLISHED;
	tipc_link_bc_ack_rcv(rcv_l, ack, xmitq);
	trace_tipc_link_reset(rcv_l, TIPC_DUMP_ALL, "bclink removed!");
	tipc_link_reset(rcv_l);
	rcv_l->state = LINK_RESET;
	if (!snd_l->ackers) {
		trace_tipc_link_reset(snd_l, TIPC_DUMP_ALL, "zero ackers!");
		tipc_link_reset(snd_l);
		snd_l->state = LINK_RESET;
		__skb_queue_purge(xmitq);
	}
}