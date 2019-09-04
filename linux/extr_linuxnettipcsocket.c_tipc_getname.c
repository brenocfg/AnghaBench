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
struct tipc_sock {int /*<<< orphan*/  portid; } ;
struct socket {struct sock* sk; } ;
struct TYPE_5__ {scalar_t__ domain; } ;
struct TYPE_4__ {int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {TYPE_2__ name; TYPE_1__ id; } ;
struct sockaddr_tipc {TYPE_3__ addr; scalar_t__ scope; int /*<<< orphan*/  family; int /*<<< orphan*/  addrtype; } ;
struct sockaddr {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_TIPC ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  TIPC_ADDR_ID ; 
 scalar_t__ TIPC_DISCONNECTING ; 
 int /*<<< orphan*/  memset (struct sockaddr_tipc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  tipc_own_addr (int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_connected (struct sock*) ; 
 int /*<<< orphan*/  tsk_peer_node (struct tipc_sock*) ; 
 int /*<<< orphan*/  tsk_peer_port (struct tipc_sock*) ; 

__attribute__((used)) static int tipc_getname(struct socket *sock, struct sockaddr *uaddr,
			int peer)
{
	struct sockaddr_tipc *addr = (struct sockaddr_tipc *)uaddr;
	struct sock *sk = sock->sk;
	struct tipc_sock *tsk = tipc_sk(sk);

	memset(addr, 0, sizeof(*addr));
	if (peer) {
		if ((!tipc_sk_connected(sk)) &&
		    ((peer != 2) || (sk->sk_state != TIPC_DISCONNECTING)))
			return -ENOTCONN;
		addr->addr.id.ref = tsk_peer_port(tsk);
		addr->addr.id.node = tsk_peer_node(tsk);
	} else {
		addr->addr.id.ref = tsk->portid;
		addr->addr.id.node = tipc_own_addr(sock_net(sk));
	}

	addr->addrtype = TIPC_ADDR_ID;
	addr->family = AF_TIPC;
	addr->scope = 0;
	addr->addr.name.domain = 0;

	return sizeof(*addr);
}