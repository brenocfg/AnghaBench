#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tipc_topsrv {struct socket* listener; int /*<<< orphan*/  net; } ;
struct socket {TYPE_3__* ops; struct sock* sk; } ;
struct TYPE_5__ {void* upper; void* lower; void* type; } ;
struct TYPE_6__ {TYPE_1__ nameseq; } ;
struct sockaddr_tipc {int /*<<< orphan*/  scope; TYPE_2__ addr; int /*<<< orphan*/  addrtype; int /*<<< orphan*/  family; } ;
struct sockaddr {int dummy; } ;
struct sock {TYPE_4__* sk_prot_creator; int /*<<< orphan*/  sk_callback_lock; struct tipc_topsrv* sk_user_data; int /*<<< orphan*/  sk_data_ready; } ;
typedef  int /*<<< orphan*/  saddr ;
typedef  int /*<<< orphan*/  imp ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_TIPC ; 
 int EINVAL ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  SOL_TIPC ; 
 int /*<<< orphan*/  TIPC_ADDR_NAMESEQ ; 
 int TIPC_CRITICAL_IMPORTANCE ; 
 int /*<<< orphan*/  TIPC_IMPORTANCE ; 
 int /*<<< orphan*/  TIPC_NODE_SCOPE ; 
 void* TIPC_TOP_SRV ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_listen (struct socket*,int /*<<< orphan*/ ) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  tipc_topsrv_listener_data_ready ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tipc_topsrv_create_listener(struct tipc_topsrv *srv)
{
	int imp = TIPC_CRITICAL_IMPORTANCE;
	struct socket *lsock = NULL;
	struct sockaddr_tipc saddr;
	struct sock *sk;
	int rc;

	rc = sock_create_kern(srv->net, AF_TIPC, SOCK_SEQPACKET, 0, &lsock);
	if (rc < 0)
		return rc;

	srv->listener = lsock;
	sk = lsock->sk;
	write_lock_bh(&sk->sk_callback_lock);
	sk->sk_data_ready = tipc_topsrv_listener_data_ready;
	sk->sk_user_data = srv;
	write_unlock_bh(&sk->sk_callback_lock);

	rc = kernel_setsockopt(lsock, SOL_TIPC, TIPC_IMPORTANCE,
			       (char *)&imp, sizeof(imp));
	if (rc < 0)
		goto err;

	saddr.family	                = AF_TIPC;
	saddr.addrtype		        = TIPC_ADDR_NAMESEQ;
	saddr.addr.nameseq.type	        = TIPC_TOP_SRV;
	saddr.addr.nameseq.lower	= TIPC_TOP_SRV;
	saddr.addr.nameseq.upper	= TIPC_TOP_SRV;
	saddr.scope			= TIPC_NODE_SCOPE;

	rc = kernel_bind(lsock, (struct sockaddr *)&saddr, sizeof(saddr));
	if (rc < 0)
		goto err;
	rc = kernel_listen(lsock, 0);
	if (rc < 0)
		goto err;

	/* As server's listening socket owner and creator is the same module,
	 * we have to decrease TIPC module reference count to guarantee that
	 * it remains zero after the server socket is created, otherwise,
	 * executing "rmmod" command is unable to make TIPC module deleted
	 * after TIPC module is inserted successfully.
	 *
	 * However, the reference count is ever increased twice in
	 * sock_create_kern(): one is to increase the reference count of owner
	 * of TIPC socket's proto_ops struct; another is to increment the
	 * reference count of owner of TIPC proto struct. Therefore, we must
	 * decrement the module reference count twice to ensure that it keeps
	 * zero after server's listening socket is created. Of course, we
	 * must bump the module reference count twice as well before the socket
	 * is closed.
	 */
	module_put(lsock->ops->owner);
	module_put(sk->sk_prot_creator->owner);

	return 0;
err:
	sock_release(lsock);
	return -EINVAL;
}