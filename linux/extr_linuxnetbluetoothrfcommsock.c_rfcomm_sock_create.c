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
struct socket {scalar_t__ type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct socket*) ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 struct sock* rfcomm_sock_alloc (struct net*,struct socket*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rfcomm_sock_init (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_sock_ops ; 

__attribute__((used)) static int rfcomm_sock_create(struct net *net, struct socket *sock,
			      int protocol, int kern)
{
	struct sock *sk;

	BT_DBG("sock %p", sock);

	sock->state = SS_UNCONNECTED;

	if (sock->type != SOCK_STREAM && sock->type != SOCK_RAW)
		return -ESOCKTNOSUPPORT;

	sock->ops = &rfcomm_sock_ops;

	sk = rfcomm_sock_alloc(net, sock, protocol, GFP_ATOMIC, kern);
	if (!sk)
		return -ENOMEM;

	rfcomm_sock_init(sk, NULL);
	return 0;
}