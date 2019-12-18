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
struct TYPE_2__ {int /*<<< orphan*/  sent_acks; } ;
struct tipc_link {int rcv_nxt; int snd_nxt; TYPE_1__ stats; scalar_t__ rcv_unacked; int /*<<< orphan*/  net; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_MSG ; 
 int TIPC_LINK_SND_STATE ; 
 scalar_t__ link_is_bc_rcvlink (struct tipc_link*) ; 
 int /*<<< orphan*/  tipc_link_build_proto_msg (struct tipc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int tipc_own_addr (int /*<<< orphan*/ ) ; 

int tipc_link_build_state_msg(struct tipc_link *l, struct sk_buff_head *xmitq)
{
	if (!l)
		return 0;

	/* Broadcast ACK must be sent via a unicast link => defer to caller */
	if (link_is_bc_rcvlink(l)) {
		if (((l->rcv_nxt ^ tipc_own_addr(l->net)) & 0xf) != 0xf)
			return 0;
		l->rcv_unacked = 0;

		/* Use snd_nxt to store peer's snd_nxt in broadcast rcv link */
		l->snd_nxt = l->rcv_nxt;
		return TIPC_LINK_SND_STATE;
	}

	/* Unicast ACK */
	l->rcv_unacked = 0;
	l->stats.sent_acks++;
	tipc_link_build_proto_msg(l, STATE_MSG, 0, 0, 0, 0, 0, xmitq);
	return 0;
}