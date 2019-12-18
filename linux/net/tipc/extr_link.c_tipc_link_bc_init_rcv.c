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
typedef  void* u16 ;
struct tipc_msg {int dummy; } ;
struct tipc_link {int peer_caps; void* rcv_nxt; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ACTIVATE_MSG ; 
 scalar_t__ BCAST_PROTOCOL ; 
 int /*<<< orphan*/  LINK_ESTABLISHED ; 
 int RESET_MSG ; 
 int TIPC_BCAST_SYNCH ; 
 scalar_t__ link_is_up (struct tipc_link*) ; 
 void* msg_bc_snd_nxt (struct tipc_msg*) ; 
 scalar_t__ msg_peer_node_is_up (struct tipc_msg*) ; 
 int msg_type (struct tipc_msg*) ; 
 scalar_t__ msg_user (struct tipc_msg*) ; 

void tipc_link_bc_init_rcv(struct tipc_link *l, struct tipc_msg *hdr)
{
	int mtyp = msg_type(hdr);
	u16 peers_snd_nxt = msg_bc_snd_nxt(hdr);

	if (link_is_up(l))
		return;

	if (msg_user(hdr) == BCAST_PROTOCOL) {
		l->rcv_nxt = peers_snd_nxt;
		l->state = LINK_ESTABLISHED;
		return;
	}

	if (l->peer_caps & TIPC_BCAST_SYNCH)
		return;

	if (msg_peer_node_is_up(hdr))
		return;

	/* Compatibility: accept older, less safe initial synch data */
	if ((mtyp == RESET_MSG) || (mtyp == ACTIVATE_MSG))
		l->rcv_nxt = peers_snd_nxt;
}