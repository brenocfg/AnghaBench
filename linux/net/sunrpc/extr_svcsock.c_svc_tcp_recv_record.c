#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  xpt_flags; struct svc_serv* xpt_server; } ;
struct svc_sock {int sk_tcplen; scalar_t__ sk_datalen; TYPE_1__ sk_xprt; int /*<<< orphan*/  sk_reclen; } ;
struct svc_serv {scalar_t__ sv_max_mesg; } ;
struct svc_rqst {int dummy; } ;
struct kvec {char* iov_base; unsigned int iov_len; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int /*<<< orphan*/  net_notice_ratelimited (char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svc_recvfrom (struct svc_rqst*,struct kvec*,int,unsigned int,int /*<<< orphan*/ ) ; 
 int svc_sock_reclen (struct svc_sock*) ; 

__attribute__((used)) static int svc_tcp_recv_record(struct svc_sock *svsk, struct svc_rqst *rqstp)
{
	struct svc_serv	*serv = svsk->sk_xprt.xpt_server;
	unsigned int want;
	int len;

	if (svsk->sk_tcplen < sizeof(rpc_fraghdr)) {
		struct kvec	iov;

		want = sizeof(rpc_fraghdr) - svsk->sk_tcplen;
		iov.iov_base = ((char *) &svsk->sk_reclen) + svsk->sk_tcplen;
		iov.iov_len  = want;
		len = svc_recvfrom(rqstp, &iov, 1, want, 0);
		if (len < 0)
			goto error;
		svsk->sk_tcplen += len;

		if (len < want) {
			dprintk("svc: short recvfrom while reading record "
				"length (%d of %d)\n", len, want);
			return -EAGAIN;
		}

		dprintk("svc: TCP record, %d bytes\n", svc_sock_reclen(svsk));
		if (svc_sock_reclen(svsk) + svsk->sk_datalen >
							serv->sv_max_mesg) {
			net_notice_ratelimited("RPC: fragment too large: %d\n",
					svc_sock_reclen(svsk));
			goto err_delete;
		}
	}

	return svc_sock_reclen(svsk);
error:
	dprintk("RPC: TCP recv_record got %d\n", len);
	return len;
err_delete:
	set_bit(XPT_CLOSE, &svsk->sk_xprt.xpt_flags);
	return -EAGAIN;
}