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
struct sock {size_t sk_state; } ;

/* Variables and functions */
 int TCP_ACTION_FIN ; 
 int TCP_STATE_MASK ; 
 scalar_t__* new_state ; 
 int /*<<< orphan*/  tcp_set_state (struct sock*,int) ; 

__attribute__((used)) static int tcp_close_state(struct sock *sk)
{
	int next = (int)new_state[sk->sk_state];
	int ns = next & TCP_STATE_MASK;

	tcp_set_state(sk, ns);

	return next & TCP_ACTION_FIN;
}