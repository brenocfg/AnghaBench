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
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_BIND ; 
 int /*<<< orphan*/  OP_BIND ; 
 int /*<<< orphan*/  aa_sk_perm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int af_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_perm (struct socket*,struct sockaddr*,int) ; 
 int in_interrupt () ; 

__attribute__((used)) static int apparmor_socket_bind(struct socket *sock,
				struct sockaddr *address, int addrlen)
{
	AA_BUG(!sock);
	AA_BUG(!sock->sk);
	AA_BUG(!address);
	AA_BUG(in_interrupt());

	return af_select(sock->sk->sk_family,
			 bind_perm(sock, address, addrlen),
			 aa_sk_perm(OP_BIND, AA_MAY_BIND, sock->sk));
}