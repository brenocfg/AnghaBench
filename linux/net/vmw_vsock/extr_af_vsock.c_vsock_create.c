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
struct socket {int type; int /*<<< orphan*/  state; int /*<<< orphan*/ * ops; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PF_VSOCK ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 scalar_t__ __vsock_create (struct net*,struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vsock_dgram_ops ; 
 int /*<<< orphan*/  vsock_stream_ops ; 

__attribute__((used)) static int vsock_create(struct net *net, struct socket *sock,
			int protocol, int kern)
{
	if (!sock)
		return -EINVAL;

	if (protocol && protocol != PF_VSOCK)
		return -EPROTONOSUPPORT;

	switch (sock->type) {
	case SOCK_DGRAM:
		sock->ops = &vsock_dgram_ops;
		break;
	case SOCK_STREAM:
		sock->ops = &vsock_stream_ops;
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	sock->state = SS_UNCONNECTED;

	return __vsock_create(net, sock, NULL, GFP_KERNEL, 0, kern) ? 0 : -ENOMEM;
}