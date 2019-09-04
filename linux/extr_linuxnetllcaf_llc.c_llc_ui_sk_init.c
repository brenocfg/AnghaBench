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
struct socket {int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; } ;
struct sock {int /*<<< orphan*/  sk_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  llc_ui_ops ; 
 int /*<<< orphan*/  sock_graft (struct sock*,struct socket*) ; 

__attribute__((used)) static void llc_ui_sk_init(struct socket *sock, struct sock *sk)
{
	sock_graft(sk, sock);
	sk->sk_type	= sock->type;
	sock->ops	= &llc_ui_ops;
}