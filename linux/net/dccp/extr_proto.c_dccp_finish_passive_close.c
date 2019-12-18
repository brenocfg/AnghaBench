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
struct sock {int sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CLOSED ; 
 int /*<<< orphan*/  DCCP_CLOSING ; 
#define  DCCP_PASSIVE_CLOSE 129 
#define  DCCP_PASSIVE_CLOSEREQ 128 
 int /*<<< orphan*/  DCCP_RESET_CODE_CLOSED ; 
 int /*<<< orphan*/  dccp_send_close (struct sock*,int) ; 
 int /*<<< orphan*/  dccp_send_reset (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dccp_finish_passive_close(struct sock *sk)
{
	switch (sk->sk_state) {
	case DCCP_PASSIVE_CLOSE:
		/* Node (client or server) has received Close packet. */
		dccp_send_reset(sk, DCCP_RESET_CODE_CLOSED);
		dccp_set_state(sk, DCCP_CLOSED);
		break;
	case DCCP_PASSIVE_CLOSEREQ:
		/*
		 * Client received CloseReq. We set the `active' flag so that
		 * dccp_send_close() retransmits the Close as per RFC 4340, 8.3.
		 */
		dccp_send_close(sk, 1);
		dccp_set_state(sk, DCCP_CLOSING);
	}
}