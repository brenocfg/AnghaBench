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
struct nfsd_net {TYPE_1__* nfsd_serv; } ;
struct net {int dummy; } ;
struct TYPE_3__ {int sv_nrthreads; } ;

/* Variables and functions */
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  svc_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_shutdown_net (TYPE_1__*,struct net*) ; 

void nfsd_destroy(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	int destroy = (nn->nfsd_serv->sv_nrthreads == 1);

	if (destroy)
		svc_shutdown_net(nn->nfsd_serv, net);
	svc_destroy(nn->nfsd_serv);
	if (destroy)
		nn->nfsd_serv = NULL;
}