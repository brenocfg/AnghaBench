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
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int EPERM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_APPLETALK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 int /*<<< orphan*/  atalk_dgram_ops ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddp_proto ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atalk_create(struct net *net, struct socket *sock, int protocol,
			int kern)
{
	struct sock *sk;
	int rc = -ESOCKTNOSUPPORT;

	if (!net_eq(net, &init_net))
		return -EAFNOSUPPORT;

	/*
	 * We permit SOCK_DGRAM and RAW is an extension. It is trivial to do
	 * and gives you the full ELAP frame. Should be handy for CAP 8)
	 */
	if (sock->type != SOCK_RAW && sock->type != SOCK_DGRAM)
		goto out;

	rc = -EPERM;
	if (sock->type == SOCK_RAW && !kern && !capable(CAP_NET_RAW))
		goto out;

	rc = -ENOMEM;
	sk = sk_alloc(net, PF_APPLETALK, GFP_KERNEL, &ddp_proto, kern);
	if (!sk)
		goto out;
	rc = 0;
	sock->ops = &atalk_dgram_ops;
	sock_init_data(sock, sk);

	/* Checksums on by default */
	sock_set_flag(sk, SOCK_ZAPPED);
out:
	return rc;
}