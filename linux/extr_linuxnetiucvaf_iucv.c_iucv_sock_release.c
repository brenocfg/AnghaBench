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
 int /*<<< orphan*/  iucv_sock_close (struct sock*) ; 
 int /*<<< orphan*/  iucv_sock_kill (struct sock*) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 

__attribute__((used)) static int iucv_sock_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	int err = 0;

	if (!sk)
		return 0;

	iucv_sock_close(sk);

	sock_orphan(sk);
	iucv_sock_kill(sk);
	return err;
}