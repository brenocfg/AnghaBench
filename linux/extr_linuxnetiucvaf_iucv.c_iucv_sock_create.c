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
struct socket {int type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PF_IUCV ; 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 struct sock* iucv_sock_alloc (struct socket*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iucv_sock_init (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iucv_sock_ops ; 

__attribute__((used)) static int iucv_sock_create(struct net *net, struct socket *sock, int protocol,
			    int kern)
{
	struct sock *sk;

	if (protocol && protocol != PF_IUCV)
		return -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	switch (sock->type) {
	case SOCK_STREAM:
		sock->ops = &iucv_sock_ops;
		break;
	case SOCK_SEQPACKET:
		/* currently, proto ops can handle both sk types */
		sock->ops = &iucv_sock_ops;
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	sk = iucv_sock_alloc(sock, protocol, GFP_KERNEL, kern);
	if (!sk)
		return -ENOMEM;

	iucv_sock_init(sk, NULL);

	return 0;
}