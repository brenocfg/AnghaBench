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
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_create_net (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  cache_destroy_net (int /*<<< orphan*/ ,struct net*) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int nfs_cache_register_net (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dns_resolve_template ; 
 int /*<<< orphan*/  nfs_net_id ; 

int nfs_dns_resolver_cache_init(struct net *net)
{
	int err;
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	nn->nfs_dns_resolve = cache_create_net(&nfs_dns_resolve_template, net);
	if (IS_ERR(nn->nfs_dns_resolve))
		return PTR_ERR(nn->nfs_dns_resolve);

	err = nfs_cache_register_net(net, nn->nfs_dns_resolve);
	if (err)
		goto err_reg;
	return 0;

err_reg:
	cache_destroy_net(nn->nfs_dns_resolve, net);
	return err;
}