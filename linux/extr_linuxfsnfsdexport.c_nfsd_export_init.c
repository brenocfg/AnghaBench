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
struct nfsd_net {void* svc_export_cache; void* svc_expkey_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* cache_create_net (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  cache_destroy_net (void*,struct net*) ; 
 int cache_register_net (void*,struct net*) ; 
 int /*<<< orphan*/  cache_unregister_net (void*,struct net*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  svc_expkey_cache_template ; 
 int /*<<< orphan*/  svc_export_cache_template ; 

int
nfsd_export_init(struct net *net)
{
	int rv;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	dprintk("nfsd: initializing export module (net: %x).\n", net->ns.inum);

	nn->svc_export_cache = cache_create_net(&svc_export_cache_template, net);
	if (IS_ERR(nn->svc_export_cache))
		return PTR_ERR(nn->svc_export_cache);
	rv = cache_register_net(nn->svc_export_cache, net);
	if (rv)
		goto destroy_export_cache;

	nn->svc_expkey_cache = cache_create_net(&svc_expkey_cache_template, net);
	if (IS_ERR(nn->svc_expkey_cache)) {
		rv = PTR_ERR(nn->svc_expkey_cache);
		goto unregister_export_cache;
	}
	rv = cache_register_net(nn->svc_expkey_cache, net);
	if (rv)
		goto destroy_expkey_cache;
	return 0;

destroy_expkey_cache:
	cache_destroy_net(nn->svc_expkey_cache, net);
unregister_export_cache:
	cache_unregister_net(nn->svc_export_cache, net);
destroy_export_cache:
	cache_destroy_net(nn->svc_export_cache, net);
	return rv;
}