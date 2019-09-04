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
typedef  void* u32 ;
struct TYPE_4__ {void* node; int /*<<< orphan*/  ref; } ;
struct TYPE_5__ {TYPE_1__ id; } ;
struct TYPE_6__ {TYPE_2__ addr; void* scope; void* addrtype; void* family; } ;
struct tipc_sock {int /*<<< orphan*/  portid; TYPE_3__ peer; } ;
struct socket {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 void* AF_TIPC ; 
 void* TIPC_ADDR_ID ; 
 void* TIPC_NODE_SCOPE ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 void* tipc_own_addr (int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_sk_finish_conn (struct tipc_sock*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int tipc_socketpair(struct socket *sock1, struct socket *sock2)
{
	struct tipc_sock *tsk2 = tipc_sk(sock2->sk);
	struct tipc_sock *tsk1 = tipc_sk(sock1->sk);
	u32 onode = tipc_own_addr(sock_net(sock1->sk));

	tsk1->peer.family = AF_TIPC;
	tsk1->peer.addrtype = TIPC_ADDR_ID;
	tsk1->peer.scope = TIPC_NODE_SCOPE;
	tsk1->peer.addr.id.ref = tsk2->portid;
	tsk1->peer.addr.id.node = onode;
	tsk2->peer.family = AF_TIPC;
	tsk2->peer.addrtype = TIPC_ADDR_ID;
	tsk2->peer.scope = TIPC_NODE_SCOPE;
	tsk2->peer.addr.id.ref = tsk1->portid;
	tsk2->peer.addr.id.node = onode;

	tipc_sk_finish_conn(tsk1, tsk2->portid, onode);
	tipc_sk_finish_conn(tsk2, tsk1->portid, onode);
	return 0;
}