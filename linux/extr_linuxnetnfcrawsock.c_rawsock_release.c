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
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  nfc_sock_unlink (int /*<<< orphan*/ *,struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct socket*,struct sock*) ; 
 int /*<<< orphan*/  raw_sk_list ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int rawsock_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	pr_debug("sock=%p sk=%p\n", sock, sk);

	if (!sk)
		return 0;

	if (sock->type == SOCK_RAW)
		nfc_sock_unlink(&raw_sk_list, sk);

	sock_orphan(sk);
	sock_put(sk);

	return 0;
}