#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket_smack {int /*<<< orphan*/ * smk_out; int /*<<< orphan*/ * smk_in; } ;
struct socket {TYPE_1__* sk; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {struct socket_smack* sk_security; } ;

/* Variables and functions */
 int PF_INET ; 
 int PF_KTHREAD ; 
 int /*<<< orphan*/  SMACK_CIPSO_SOCKET ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  smack_known_web ; 
 int smack_netlabel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smack_socket_post_create(struct socket *sock, int family,
				    int type, int protocol, int kern)
{
	struct socket_smack *ssp;

	if (sock->sk == NULL)
		return 0;

	/*
	 * Sockets created by kernel threads receive web label.
	 */
	if (unlikely(current->flags & PF_KTHREAD)) {
		ssp = sock->sk->sk_security;
		ssp->smk_in = &smack_known_web;
		ssp->smk_out = &smack_known_web;
	}

	if (family != PF_INET)
		return 0;
	/*
	 * Set the outbound netlbl.
	 */
	return smack_netlabel(sock->sk, SMACK_CIPSO_SOCKET);
}