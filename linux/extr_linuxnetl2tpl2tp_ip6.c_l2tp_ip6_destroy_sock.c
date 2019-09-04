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
struct sock {struct l2tp_tunnel* sk_user_data; } ;
struct l2tp_tunnel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet6_destroy_sock (struct sock*) ; 
 int /*<<< orphan*/  ip6_flush_pending_frames (struct sock*) ; 
 int /*<<< orphan*/  l2tp_tunnel_delete (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static void l2tp_ip6_destroy_sock(struct sock *sk)
{
	struct l2tp_tunnel *tunnel = sk->sk_user_data;

	lock_sock(sk);
	ip6_flush_pending_frames(sk);
	release_sock(sk);

	if (tunnel)
		l2tp_tunnel_delete(tunnel);

	inet6_destroy_sock(sk);
}