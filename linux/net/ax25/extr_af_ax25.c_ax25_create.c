#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int type; int /*<<< orphan*/ * ops; } ;
struct sock {int sk_protocol; int /*<<< orphan*/  sk_destruct; } ;
struct net {int dummy; } ;
struct TYPE_4__ {struct sock* sk; } ;
typedef  TYPE_1__ ax25_cb ;
struct TYPE_5__ {TYPE_1__* cb; } ;

/* Variables and functions */
#define  AX25_P_ARP 136 
#define  AX25_P_IP 135 
#define  AX25_P_NETROM 134 
#define  AX25_P_ROSE 133 
#define  AX25_P_SEGMENT 132 
 int AX25_P_TEXT ; 
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  PF_AX25 131 
 int SK_PROTOCOL_MAX ; 
#define  SOCK_DGRAM 130 
#define  SOCK_RAW 129 
#define  SOCK_SEQPACKET 128 
 TYPE_1__* ax25_create_cb () ; 
 int /*<<< orphan*/  ax25_free_sock ; 
 int /*<<< orphan*/  ax25_proto ; 
 int /*<<< orphan*/  ax25_proto_ops ; 
 int /*<<< orphan*/  ax25_protocol_is_registered (int const) ; 
 TYPE_2__* ax25_sk (struct sock*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ *) ; 
 struct sock* sk_alloc (struct net*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sk_free (struct sock*) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 

__attribute__((used)) static int ax25_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
	struct sock *sk;
	ax25_cb *ax25;

	if (protocol < 0 || protocol > SK_PROTOCOL_MAX)
		return -EINVAL;

	if (!net_eq(net, &init_net))
		return -EAFNOSUPPORT;

	switch (sock->type) {
	case SOCK_DGRAM:
		if (protocol == 0 || protocol == PF_AX25)
			protocol = AX25_P_TEXT;
		break;

	case SOCK_SEQPACKET:
		switch (protocol) {
		case 0:
		case PF_AX25:	/* For CLX */
			protocol = AX25_P_TEXT;
			break;
		case AX25_P_SEGMENT:
#ifdef CONFIG_INET
		case AX25_P_ARP:
		case AX25_P_IP:
#endif
#ifdef CONFIG_NETROM
		case AX25_P_NETROM:
#endif
#ifdef CONFIG_ROSE
		case AX25_P_ROSE:
#endif
			return -ESOCKTNOSUPPORT;
#ifdef CONFIG_NETROM_MODULE
		case AX25_P_NETROM:
			if (ax25_protocol_is_registered(AX25_P_NETROM))
				return -ESOCKTNOSUPPORT;
			break;
#endif
#ifdef CONFIG_ROSE_MODULE
		case AX25_P_ROSE:
			if (ax25_protocol_is_registered(AX25_P_ROSE))
				return -ESOCKTNOSUPPORT;
#endif
		default:
			break;
		}
		break;

	case SOCK_RAW:
		if (!capable(CAP_NET_RAW))
			return -EPERM;
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	sk = sk_alloc(net, PF_AX25, GFP_ATOMIC, &ax25_proto, kern);
	if (sk == NULL)
		return -ENOMEM;

	ax25 = ax25_sk(sk)->cb = ax25_create_cb();
	if (!ax25) {
		sk_free(sk);
		return -ENOMEM;
	}

	sock_init_data(sock, sk);

	sk->sk_destruct = ax25_free_sock;
	sock->ops    = &ax25_proto_ops;
	sk->sk_protocol = protocol;

	ax25->sk    = sk;

	return 0;
}