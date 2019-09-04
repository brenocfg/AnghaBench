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
struct nfsd_net {int /*<<< orphan*/  svc_export_cache; int /*<<< orphan*/  svc_expkey_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_destroy_net (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  cache_unregister_net (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  svcauth_unix_purge (struct net*) ; 

void
nfsd_export_shutdown(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprintk("nfsd: shutting down export module (net: %x).\n", net->ns.inum);

	cache_unregister_net(nn->svc_expkey_cache, net);
	cache_unregister_net(nn->svc_export_cache, net);
	cache_destroy_net(nn->svc_expkey_cache, net);
	cache_destroy_net(nn->svc_export_cache, net);
	svcauth_unix_purge(net);

	dprintk("nfsd: export shutdown complete (net: %x).\n", net->ns.inum);
}