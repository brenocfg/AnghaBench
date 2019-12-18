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
struct nfsd_net {TYPE_1__* nfsd_serv; } ;
struct net {int dummy; } ;
struct cred {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sv_permsocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_PORT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SVC_SOCK_DEFAULTS ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int svc_create_xprt (TYPE_1__*,char*,struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cred const*) ; 

__attribute__((used)) static int nfsd_init_socks(struct net *net, const struct cred *cred)
{
	int error;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	if (!list_empty(&nn->nfsd_serv->sv_permsocks))
		return 0;

	error = svc_create_xprt(nn->nfsd_serv, "udp", net, PF_INET, NFS_PORT,
					SVC_SOCK_DEFAULTS, cred);
	if (error < 0)
		return error;

	error = svc_create_xprt(nn->nfsd_serv, "tcp", net, PF_INET, NFS_PORT,
					SVC_SOCK_DEFAULTS, cred);
	if (error < 0)
		return error;

	return 0;
}