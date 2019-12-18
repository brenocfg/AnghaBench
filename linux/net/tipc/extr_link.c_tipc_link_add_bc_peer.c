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
struct tipc_link {int /*<<< orphan*/  state; scalar_t__ snd_nxt; scalar_t__ acked; int /*<<< orphan*/  ackers; struct tipc_link* bc_rcvlink; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_ESTABLISHED ; 
 int /*<<< orphan*/  tipc_link_build_bc_init_msg (struct tipc_link*,struct sk_buff_head*) ; 

void tipc_link_add_bc_peer(struct tipc_link *snd_l,
			   struct tipc_link *uc_l,
			   struct sk_buff_head *xmitq)
{
	struct tipc_link *rcv_l = uc_l->bc_rcvlink;

	snd_l->ackers++;
	rcv_l->acked = snd_l->snd_nxt - 1;
	snd_l->state = LINK_ESTABLISHED;
	tipc_link_build_bc_init_msg(uc_l, xmitq);
}