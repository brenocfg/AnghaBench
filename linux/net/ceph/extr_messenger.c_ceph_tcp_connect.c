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
struct socket {TYPE_2__* sk; TYPE_1__* ops; } ;
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_8__ {struct sockaddr_storage in_addr; } ;
struct ceph_connection {struct socket* sock; TYPE_3__* msgr; TYPE_4__ peer_addr; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  optval ;
struct TYPE_7__ {int /*<<< orphan*/  net; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_lock; int /*<<< orphan*/  sk_allocation; } ;
struct TYPE_5__ {int (* connect ) (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct socket*) ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  ceph_pr_addr (TYPE_4__*) ; 
 scalar_t__ ceph_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_sock_state_connecting (struct ceph_connection*) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  from_msgr (TYPE_3__*) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memalloc_noio_restore (unsigned int) ; 
 unsigned int memalloc_noio_save () ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_sock_callbacks (struct socket*,struct ceph_connection*) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  socket_class ; 
 int stub1 (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_tcp_connect(struct ceph_connection *con)
{
	struct sockaddr_storage ss = con->peer_addr.in_addr; /* align */
	struct socket *sock;
	unsigned int noio_flag;
	int ret;

	BUG_ON(con->sock);

	/* sock_create_kern() allocates with GFP_KERNEL */
	noio_flag = memalloc_noio_save();
	ret = sock_create_kern(read_pnet(&con->msgr->net), ss.ss_family,
			       SOCK_STREAM, IPPROTO_TCP, &sock);
	memalloc_noio_restore(noio_flag);
	if (ret)
		return ret;
	sock->sk->sk_allocation = GFP_NOFS;

#ifdef CONFIG_LOCKDEP
	lockdep_set_class(&sock->sk->sk_lock, &socket_class);
#endif

	set_sock_callbacks(sock, con);

	dout("connect %s\n", ceph_pr_addr(&con->peer_addr));

	con_sock_state_connecting(con);
	ret = sock->ops->connect(sock, (struct sockaddr *)&ss, sizeof(ss),
				 O_NONBLOCK);
	if (ret == -EINPROGRESS) {
		dout("connect %s EINPROGRESS sk_state = %u\n",
		     ceph_pr_addr(&con->peer_addr),
		     sock->sk->sk_state);
	} else if (ret < 0) {
		pr_err("connect %s error %d\n",
		       ceph_pr_addr(&con->peer_addr), ret);
		sock_release(sock);
		return ret;
	}

	if (ceph_test_opt(from_msgr(con->msgr), TCP_NODELAY)) {
		int optval = 1;

		ret = kernel_setsockopt(sock, SOL_TCP, TCP_NODELAY,
					(char *)&optval, sizeof(optval));
		if (ret)
			pr_err("kernel_setsockopt(TCP_NODELAY) failed: %d",
			       ret);
	}

	con->sock = sock;
	return 0;
}