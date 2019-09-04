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
struct sock {scalar_t__ sk_net_refcnt; } ;

/* Variables and functions */
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  sk_destruct (struct sock*) ; 
 int /*<<< orphan*/  sock_diag_broadcast_destroy (struct sock*) ; 
 scalar_t__ sock_diag_has_destroy_listeners (struct sock*) ; 
 int /*<<< orphan*/  sock_inuse_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __sk_free(struct sock *sk)
{
	if (likely(sk->sk_net_refcnt))
		sock_inuse_add(sock_net(sk), -1);

	if (unlikely(sk->sk_net_refcnt && sock_diag_has_destroy_listeners(sk)))
		sock_diag_broadcast_destroy(sk);
	else
		sk_destruct(sk);
}