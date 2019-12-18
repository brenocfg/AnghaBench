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
struct TYPE_6__ {int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_remotebuf; } ;
struct svc_sock {TYPE_3__ sk_xprt; int /*<<< orphan*/ * sk_pages; scalar_t__ sk_datalen; scalar_t__ sk_tcplen; scalar_t__ sk_reclen; TYPE_1__* sk_sock; struct sock* sk_sk; } ;
struct svc_serv {int dummy; } ;
struct sock {int sk_state; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; } ;
struct TYPE_5__ {int /*<<< orphan*/  nonagle; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
#define  TCP_ESTABLISHED 129 
 int TCP_LISTEN ; 
 int /*<<< orphan*/  TCP_NAGLE_OFF ; 
#define  TCP_SYN_RECV 128 
 int /*<<< orphan*/  XPT_CACHE_AUTH ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  XPT_CONG_CTRL ; 
 int /*<<< orphan*/  XPT_CONN ; 
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  XPT_LISTENER ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svc_data_ready ; 
 int /*<<< orphan*/  svc_tcp_class ; 
 int /*<<< orphan*/  svc_tcp_listen_data_ready ; 
 int /*<<< orphan*/  svc_tcp_state_change ; 
 int /*<<< orphan*/  svc_write_space ; 
 int /*<<< orphan*/  svc_xprt_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,struct svc_serv*) ; 
 TYPE_2__* tcp_sk (struct sock*) ; 

__attribute__((used)) static void svc_tcp_init(struct svc_sock *svsk, struct svc_serv *serv)
{
	struct sock	*sk = svsk->sk_sk;

	svc_xprt_init(sock_net(svsk->sk_sock->sk), &svc_tcp_class,
		      &svsk->sk_xprt, serv);
	set_bit(XPT_CACHE_AUTH, &svsk->sk_xprt.xpt_flags);
	set_bit(XPT_CONG_CTRL, &svsk->sk_xprt.xpt_flags);
	if (sk->sk_state == TCP_LISTEN) {
		dprintk("setting up TCP socket for listening\n");
		strcpy(svsk->sk_xprt.xpt_remotebuf, "listener");
		set_bit(XPT_LISTENER, &svsk->sk_xprt.xpt_flags);
		sk->sk_data_ready = svc_tcp_listen_data_ready;
		set_bit(XPT_CONN, &svsk->sk_xprt.xpt_flags);
	} else {
		dprintk("setting up TCP socket for reading\n");
		sk->sk_state_change = svc_tcp_state_change;
		sk->sk_data_ready = svc_data_ready;
		sk->sk_write_space = svc_write_space;

		svsk->sk_reclen = 0;
		svsk->sk_tcplen = 0;
		svsk->sk_datalen = 0;
		memset(&svsk->sk_pages[0], 0, sizeof(svsk->sk_pages));

		tcp_sk(sk)->nonagle |= TCP_NAGLE_OFF;

		set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
		switch (sk->sk_state) {
		case TCP_SYN_RECV:
		case TCP_ESTABLISHED:
			break;
		default:
			set_bit(XPT_CLOSE, &svsk->sk_xprt.xpt_flags);
		}
	}
}