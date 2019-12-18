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
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  vcc_destroy_socket (struct sock*) ; 

int vcc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (sk) {
		lock_sock(sk);
		vcc_destroy_socket(sock->sk);
		release_sock(sk);
		sock_put(sk);
	}

	return 0;
}