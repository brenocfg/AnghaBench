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
struct nfs_net {int /*<<< orphan*/  nfs_dns_resolve; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_destroy_net (int /*<<< orphan*/ ,struct net*) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_cache_unregister_net (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_net_id ; 

void nfs_dns_resolver_cache_destroy(struct net *net)
{
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	nfs_cache_unregister_net(net, nn->nfs_dns_resolve);
	cache_destroy_net(nn->nfs_dns_resolve, net);
}