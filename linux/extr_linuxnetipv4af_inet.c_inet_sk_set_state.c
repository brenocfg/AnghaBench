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
 int /*<<< orphan*/  trace_inet_sock_set_state (struct sock*,int,int) ; 

void inet_sk_set_state(struct sock *sk, int state)
{
	trace_inet_sock_set_state(sk, sk->sk_state, state);
	sk->sk_state = state;
}