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
struct svc_serv {int dummy; } ;
struct nfs_net {int nfs_callback_tcpport; int nfs_callback_tcpport6; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SVC_SOCK_ANONYMOUS ; 
 struct cred* current_cred () ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_callback_set_tcpport ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int svc_create_xprt (struct svc_serv*,char*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*) ; 

__attribute__((used)) static int nfs4_callback_up_net(struct svc_serv *serv, struct net *net)
{
	const struct cred *cred = current_cred();
	int ret;
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	ret = svc_create_xprt(serv, "tcp", net, PF_INET,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS,
				cred);
	if (ret <= 0)
		goto out_err;
	nn->nfs_callback_tcpport = ret;
	dprintk("NFS: Callback listener port = %u (af %u, net %x)\n",
		nn->nfs_callback_tcpport, PF_INET, net->ns.inum);

	ret = svc_create_xprt(serv, "tcp", net, PF_INET6,
				nfs_callback_set_tcpport, SVC_SOCK_ANONYMOUS,
				cred);
	if (ret > 0) {
		nn->nfs_callback_tcpport6 = ret;
		dprintk("NFS: Callback listener port = %u (af %u, net %x)\n",
			nn->nfs_callback_tcpport6, PF_INET6, net->ns.inum);
	} else if (ret != -EAFNOSUPPORT)
		goto out_err;
	return 0;

out_err:
	return (ret) ? ret : -ENOMEM;
}