#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_xprt {int dummy; } ;
struct nfsd_net {TYPE_1__* nfsd_serv; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  sv_nrthreads; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int EINVAL ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SVC_SOCK_ANONYMOUS ; 
 int USHRT_MAX ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nfsd_create_serv (struct net*) ; 
 int /*<<< orphan*/  nfsd_destroy (struct net*) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int sscanf (char*,char*,char*,int*) ; 
 int /*<<< orphan*/  svc_close_xprt (struct svc_xprt*) ; 
 int svc_create_xprt (TYPE_1__*,char*,struct net*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct cred const*) ; 
 struct svc_xprt* svc_find_xprt (TYPE_1__*,char*,struct net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svc_xprt_put (struct svc_xprt*) ; 

__attribute__((used)) static ssize_t __write_ports_addxprt(char *buf, struct net *net, const struct cred *cred)
{
	char transport[16];
	struct svc_xprt *xprt;
	int port, err;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	if (sscanf(buf, "%15s %5u", transport, &port) != 2)
		return -EINVAL;

	if (port < 1 || port > USHRT_MAX)
		return -EINVAL;

	err = nfsd_create_serv(net);
	if (err != 0)
		return err;

	err = svc_create_xprt(nn->nfsd_serv, transport, net,
				PF_INET, port, SVC_SOCK_ANONYMOUS, cred);
	if (err < 0)
		goto out_err;

	err = svc_create_xprt(nn->nfsd_serv, transport, net,
				PF_INET6, port, SVC_SOCK_ANONYMOUS, cred);
	if (err < 0 && err != -EAFNOSUPPORT)
		goto out_close;

	/* Decrease the count, but don't shut down the service */
	nn->nfsd_serv->sv_nrthreads--;
	return 0;
out_close:
	xprt = svc_find_xprt(nn->nfsd_serv, transport, net, PF_INET, port);
	if (xprt != NULL) {
		svc_close_xprt(xprt);
		svc_xprt_put(xprt);
	}
out_err:
	nfsd_destroy(net);
	return err;
}