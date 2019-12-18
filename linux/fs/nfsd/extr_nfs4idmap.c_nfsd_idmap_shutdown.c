#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfsd_net {int /*<<< orphan*/  nametoid_cache; int /*<<< orphan*/  idtoname_cache; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_destroy_net (int /*<<< orphan*/ ,struct net*) ; 
 int /*<<< orphan*/  cache_unregister_net (int /*<<< orphan*/ ,struct net*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 

void
nfsd_idmap_shutdown(struct net *net)
{
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	cache_unregister_net(nn->idtoname_cache, net);
	cache_unregister_net(nn->nametoid_cache, net);
	cache_destroy_net(nn->idtoname_cache, net);
	cache_destroy_net(nn->nametoid_cache, net);
}