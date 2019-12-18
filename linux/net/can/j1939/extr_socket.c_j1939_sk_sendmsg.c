#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/  name; int /*<<< orphan*/  pgn; } ;
struct TYPE_5__ {TYPE_1__ j1939; } ;
struct sockaddr_can {scalar_t__ can_family; int can_ifindex; TYPE_2__ can_addr; } ;
struct sock {int dummy; } ;
struct msghdr {scalar_t__ msg_namelen; struct sockaddr_can* msg_name; } ;
struct TYPE_6__ {scalar_t__ sa; scalar_t__ da; int /*<<< orphan*/  dst_name; int /*<<< orphan*/  src_name; } ;
struct j1939_sock {int state; int ifindex; TYPE_3__ addr; struct j1939_priv* priv; } ;
struct j1939_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_CAN ; 
 int EACCES ; 
 int EBADFD ; 
 int EINVAL ; 
 scalar_t__ J1939_MIN_NAMELEN ; 
 scalar_t__ J1939_NO_ADDR ; 
 int J1939_SOCK_BOUND ; 
 int /*<<< orphan*/  SOCK_BROADCAST ; 
 int /*<<< orphan*/  j1939_pgn_is_clean_pdu (int /*<<< orphan*/ ) ; 
 scalar_t__ j1939_pgn_is_valid (int /*<<< orphan*/ ) ; 
 struct j1939_sock* j1939_sk (struct sock*) ; 
 int j1939_sk_send_loop (struct j1939_priv*,struct sock*,struct msghdr*,size_t) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int j1939_sk_sendmsg(struct socket *sock, struct msghdr *msg,
			    size_t size)
{
	struct sock *sk = sock->sk;
	struct j1939_sock *jsk = j1939_sk(sk);
	struct j1939_priv *priv = jsk->priv;
	int ifindex;
	int ret;

	/* various socket state tests */
	if (!(jsk->state & J1939_SOCK_BOUND))
		return -EBADFD;

	ifindex = jsk->ifindex;

	if (!jsk->addr.src_name && jsk->addr.sa == J1939_NO_ADDR)
		/* no source address assigned yet */
		return -EBADFD;

	/* deal with provided destination address info */
	if (msg->msg_name) {
		struct sockaddr_can *addr = msg->msg_name;

		if (msg->msg_namelen < J1939_MIN_NAMELEN)
			return -EINVAL;

		if (addr->can_family != AF_CAN)
			return -EINVAL;

		if (addr->can_ifindex && addr->can_ifindex != ifindex)
			return -EBADFD;

		if (j1939_pgn_is_valid(addr->can_addr.j1939.pgn) &&
		    !j1939_pgn_is_clean_pdu(addr->can_addr.j1939.pgn))
			return -EINVAL;

		if (!addr->can_addr.j1939.name &&
		    addr->can_addr.j1939.addr == J1939_NO_ADDR &&
		    !sock_flag(sk, SOCK_BROADCAST))
			/* broadcast, but SO_BROADCAST not set */
			return -EACCES;
	} else {
		if (!jsk->addr.dst_name && jsk->addr.da == J1939_NO_ADDR &&
		    !sock_flag(sk, SOCK_BROADCAST))
			/* broadcast, but SO_BROADCAST not set */
			return -EACCES;
	}

	ret = j1939_sk_send_loop(priv, sk, msg, size);

	return ret;
}