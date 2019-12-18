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
struct socket {TYPE_1__* sk; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_LISTEN ; 
 int /*<<< orphan*/  OP_LISTEN ; 
 int /*<<< orphan*/  aa_sk_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int af_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int in_interrupt () ; 
 int /*<<< orphan*/  listen_perm (struct socket*,int) ; 

__attribute__((used)) static int apparmor_socket_listen(struct socket *sock, int backlog)
{
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(in_interrupt());

	return af_select(sock->sk->sk_family,
			 listen_perm(sock, backlog),
			 aa_sk_perm(OP_LISTEN, AA_MAY_LISTEN, sock->sk));
}