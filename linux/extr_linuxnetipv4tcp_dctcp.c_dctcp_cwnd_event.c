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
struct sock {int dummy; } ;
typedef  enum tcp_ca_event { ____Placeholder_tcp_ca_event } tcp_ca_event ;

/* Variables and functions */
#define  CA_EVENT_ECN_IS_CE 130 
#define  CA_EVENT_ECN_NO_CE 129 
#define  CA_EVENT_LOSS 128 
 int /*<<< orphan*/  dctcp_ce_state_0_to_1 (struct sock*) ; 
 int /*<<< orphan*/  dctcp_ce_state_1_to_0 (struct sock*) ; 
 int /*<<< orphan*/  dctcp_react_to_loss (struct sock*) ; 

__attribute__((used)) static void dctcp_cwnd_event(struct sock *sk, enum tcp_ca_event ev)
{
	switch (ev) {
	case CA_EVENT_ECN_IS_CE:
		dctcp_ce_state_0_to_1(sk);
		break;
	case CA_EVENT_ECN_NO_CE:
		dctcp_ce_state_1_to_0(sk);
		break;
	case CA_EVENT_LOSS:
		dctcp_react_to_loss(sk);
		break;
	default:
		/* Don't care for the rest. */
		break;
	}
}