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
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int ESOCKTNOSUPPORT ; 
 int PF_UNIX ; 
#define  SOCK_DGRAM 131 
#define  SOCK_RAW 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 scalar_t__ unix_create1 (struct net*,struct socket*,int) ; 
 int /*<<< orphan*/  unix_dgram_ops ; 
 int /*<<< orphan*/  unix_seqpacket_ops ; 
 int /*<<< orphan*/  unix_stream_ops ; 

__attribute__((used)) static int unix_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
	if (protocol && protocol != PF_UNIX)
		return -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	switch (sock->type) {
	case SOCK_STREAM:
		sock->ops = &unix_stream_ops;
		break;
		/*
		 *	Believe it or not BSD has AF_UNIX, SOCK_RAW though
		 *	nothing uses it.
		 */
	case SOCK_RAW:
		sock->type = SOCK_DGRAM;
		/* fall through */
	case SOCK_DGRAM:
		sock->ops = &unix_dgram_ops;
		break;
	case SOCK_SEQPACKET:
		sock->ops = &unix_seqpacket_ops;
		break;
	default:
		return -ESOCKTNOSUPPORT;
	}

	return unix_create1(net, sock, kern) ? 0 : -ENOMEM;
}