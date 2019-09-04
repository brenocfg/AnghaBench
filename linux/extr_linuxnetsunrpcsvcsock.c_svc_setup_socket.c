#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xpt_flags; } ;
struct svc_sock {TYPE_1__ sk_xprt; struct sock* sk_sk; int /*<<< orphan*/  sk_owspace; int /*<<< orphan*/  sk_odata; int /*<<< orphan*/  sk_ostate; struct socket* sk_sock; } ;
struct svc_serv {int dummy; } ;
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {struct svc_sock* sk_user_data; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  inet_sport; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct svc_sock* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SOCK_DGRAM ; 
 int SVC_SOCK_ANONYMOUS ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  XPT_LISTENER ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree (struct svc_sock*) ; 
 struct svc_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int svc_register (struct svc_serv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_tcp_init (struct svc_sock*,struct svc_serv*) ; 
 int /*<<< orphan*/  svc_udp_init (struct svc_sock*,struct svc_serv*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static struct svc_sock *svc_setup_socket(struct svc_serv *serv,
						struct socket *sock,
						int flags)
{
	struct svc_sock	*svsk;
	struct sock	*inet;
	int		pmap_register = !(flags & SVC_SOCK_ANONYMOUS);
	int		err = 0;

	dprintk("svc: svc_setup_socket %p\n", sock);
	svsk = kzalloc(sizeof(*svsk), GFP_KERNEL);
	if (!svsk)
		return ERR_PTR(-ENOMEM);

	inet = sock->sk;

	/* Register socket with portmapper */
	if (pmap_register)
		err = svc_register(serv, sock_net(sock->sk), inet->sk_family,
				     inet->sk_protocol,
				     ntohs(inet_sk(inet)->inet_sport));

	if (err < 0) {
		kfree(svsk);
		return ERR_PTR(err);
	}

	svsk->sk_sock = sock;
	svsk->sk_sk = inet;
	svsk->sk_ostate = inet->sk_state_change;
	svsk->sk_odata = inet->sk_data_ready;
	svsk->sk_owspace = inet->sk_write_space;
	/*
	 * This barrier is necessary in order to prevent race condition
	 * with svc_data_ready(), svc_listen_data_ready() and others
	 * when calling callbacks above.
	 */
	wmb();
	inet->sk_user_data = svsk;

	/* Initialize the socket */
	if (sock->type == SOCK_DGRAM)
		svc_udp_init(svsk, serv);
	else
		svc_tcp_init(svsk, serv);

	dprintk("svc: svc_setup_socket created %p (inet %p), "
			"listen %d close %d\n",
			svsk, svsk->sk_sk,
			test_bit(XPT_LISTENER, &svsk->sk_xprt.xpt_flags),
			test_bit(XPT_CLOSE, &svsk->sk_xprt.xpt_flags));

	return svsk;
}