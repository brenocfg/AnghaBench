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
struct socket {int type; } ;
struct sock {int sk_protocol; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int DNPROTO_NSP ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SK_PROTOCOL_MAX ; 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 struct sock* dn_alloc_sock (struct net*,struct socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dn_create(struct net *net, struct socket *sock, int protocol,
		     int kern)
{
	struct sock *sk;

	if (protocol < 0 || protocol > SK_PROTOCOL_MAX)
		return -EINVAL;

	if (!net_eq(net, &init_net))
		return -EAFNOSUPPORT;

	switch (sock->type) {
	case SOCK_SEQPACKET:
		if (protocol != DNPROTO_NSP)
			return -EPROTONOSUPPORT;
		break;
	case SOCK_STREAM:
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}


	if ((sk = dn_alloc_sock(net, sock, GFP_KERNEL, kern)) == NULL)
		return -ENOBUFS;

	sk->sk_protocol = protocol;

	return 0;
}