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
struct TYPE_5__ {int /*<<< orphan*/  xpt_flags; } ;
struct svc_sock {TYPE_3__* sk_sock; TYPE_1__* sk_sk; TYPE_2__ sk_xprt; } ;
struct svc_serv {int dummy; } ;
typedef  int /*<<< orphan*/  one ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {int sk_family; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  BUG () ; 
 int IPV6_RECVPKTINFO ; 
 int IP_PKTINFO ; 
 int SOL_IP ; 
 int SOL_IPV6 ; 
 int /*<<< orphan*/  XPT_CACHE_AUTH ; 
 int /*<<< orphan*/  XPT_CHNGBUF ; 
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int kernel_setsockopt (TYPE_3__*,int,int,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_data_ready ; 
 int /*<<< orphan*/  svc_sock_setbufsize (struct svc_sock*,int) ; 
 int /*<<< orphan*/  svc_udp_class ; 
 int /*<<< orphan*/  svc_write_space ; 
 int /*<<< orphan*/  svc_xprt_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,struct svc_serv*) ; 

__attribute__((used)) static void svc_udp_init(struct svc_sock *svsk, struct svc_serv *serv)
{
	int err, level, optname, one = 1;

	svc_xprt_init(sock_net(svsk->sk_sock->sk), &svc_udp_class,
		      &svsk->sk_xprt, serv);
	clear_bit(XPT_CACHE_AUTH, &svsk->sk_xprt.xpt_flags);
	svsk->sk_sk->sk_data_ready = svc_data_ready;
	svsk->sk_sk->sk_write_space = svc_write_space;

	/* initialise setting must have enough space to
	 * receive and respond to one request.
	 * svc_udp_recvfrom will re-adjust if necessary
	 */
	svc_sock_setbufsize(svsk, 3);

	/* data might have come in before data_ready set up */
	set_bit(XPT_DATA, &svsk->sk_xprt.xpt_flags);
	set_bit(XPT_CHNGBUF, &svsk->sk_xprt.xpt_flags);

	/* make sure we get destination address info */
	switch (svsk->sk_sk->sk_family) {
	case AF_INET:
		level = SOL_IP;
		optname = IP_PKTINFO;
		break;
	case AF_INET6:
		level = SOL_IPV6;
		optname = IPV6_RECVPKTINFO;
		break;
	default:
		BUG();
	}
	err = kernel_setsockopt(svsk->sk_sock, level, optname,
					(char *)&one, sizeof(one));
	dprintk("svc: kernel_setsockopt returned %d\n", err);
}