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
struct sock {int /*<<< orphan*/  sk_tsq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_TSQ_DEFERRED ; 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_owned_by_user (struct sock*) ; 
 int /*<<< orphan*/  tcp_tsq_write (struct sock*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcp_tsq_handler(struct sock *sk)
{
	bh_lock_sock(sk);
	if (!sock_owned_by_user(sk))
		tcp_tsq_write(sk);
	else if (!test_and_set_bit(TCP_TSQ_DEFERRED, &sk->sk_tsq_flags))
		sock_hold(sk);
	bh_unlock_sock(sk);
}