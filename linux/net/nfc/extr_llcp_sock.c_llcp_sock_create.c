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
struct nfc_protocol {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int ENOMEM ; 
 int EPERM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_RAW ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llcp_rawsock_ops ; 
 int /*<<< orphan*/  llcp_sock_ops ; 
 struct sock* nfc_llcp_sock_alloc (struct socket*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct socket*) ; 

__attribute__((used)) static int llcp_sock_create(struct net *net, struct socket *sock,
			    const struct nfc_protocol *nfc_proto, int kern)
{
	struct sock *sk;

	pr_debug("%p\n", sock);

	if (sock->type != SOCK_STREAM &&
	    sock->type != SOCK_DGRAM &&
	    sock->type != SOCK_RAW)
		return -ESOCKTNOSUPPORT;

	if (sock->type == SOCK_RAW) {
		if (!capable(CAP_NET_RAW))
			return -EPERM;
		sock->ops = &llcp_rawsock_ops;
	} else {
		sock->ops = &llcp_sock_ops;
	}

	sk = nfc_llcp_sock_alloc(sock, sock->type, GFP_ATOMIC, kern);
	if (sk == NULL)
		return -ENOMEM;

	return 0;
}