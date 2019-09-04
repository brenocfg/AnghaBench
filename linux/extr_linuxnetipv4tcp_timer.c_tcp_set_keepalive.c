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
 int /*<<< orphan*/  SOCK_KEEPOPEN ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int /*<<< orphan*/  inet_csk_delete_keepalive_timer (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_keepalive_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keepalive_time_when (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 

void tcp_set_keepalive(struct sock *sk, int val)
{
	if ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN))
		return;

	if (val && !sock_flag(sk, SOCK_KEEPOPEN))
		inet_csk_reset_keepalive_timer(sk, keepalive_time_when(tcp_sk(sk)));
	else if (!val)
		inet_csk_delete_keepalive_timer(sk);
}