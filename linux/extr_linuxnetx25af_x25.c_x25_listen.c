#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {scalar_t__ sk_state; int sk_max_ack_backlog; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  X25_ADDR_LEN ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 TYPE_1__* x25_sk (struct sock*) ; 

__attribute__((used)) static int x25_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int rc = -EOPNOTSUPP;

	lock_sock(sk);
	if (sk->sk_state != TCP_LISTEN) {
		memset(&x25_sk(sk)->dest_addr, 0, X25_ADDR_LEN);
		sk->sk_max_ack_backlog = backlog;
		sk->sk_state           = TCP_LISTEN;
		rc = 0;
	}
	release_sock(sk);

	return rc;
}