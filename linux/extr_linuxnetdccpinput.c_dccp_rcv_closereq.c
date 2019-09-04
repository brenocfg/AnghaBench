#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int sk_state; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_seq; } ;
struct TYPE_3__ {scalar_t__ dccps_role; } ;

/* Variables and functions */
 int DCCP_CLOSING ; 
#define  DCCP_OPEN 131 
#define  DCCP_PARTOPEN 130 
#define  DCCP_PASSIVE_CLOSEREQ 129 
 int /*<<< orphan*/  DCCP_PKT_SYNC ; 
#define  DCCP_REQUESTING 128 
 scalar_t__ DCCP_ROLE_CLIENT ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  POLL_HUP ; 
 int /*<<< orphan*/  SOCK_WAKE_WAITD ; 
 int /*<<< orphan*/  dccp_fin (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_send_close (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_send_sync (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_rcv_closereq(struct sock *sk, struct sk_buff *skb)
{
	int queued = 0;

	/*
	 *   Step 7: Check for unexpected packet types
	 *      If (S.is_server and P.type == CloseReq)
	 *	  Send Sync packet acknowledging P.seqno
	 *	  Drop packet and return
	 */
	if (dccp_sk(sk)->dccps_role != DCCP_ROLE_CLIENT) {
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq, DCCP_PKT_SYNC);
		return queued;
	}

	/* Step 13: process relevant Client states < CLOSEREQ */
	switch (sk->sk_state) {
	case DCCP_REQUESTING:
		dccp_send_close(sk, 0);
		dccp_set_state(sk, DCCP_CLOSING);
		break;
	case DCCP_OPEN:
	case DCCP_PARTOPEN:
		/* Give waiting application a chance to read pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CLOSEREQ);
		/* fall through */
	case DCCP_PASSIVE_CLOSEREQ:
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	}
	return queued;
}