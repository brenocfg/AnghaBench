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
struct sunrpc_net {struct cache_detail* ip_map_cache; } ;
struct net {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct cache_detail*) ; 
 int PTR_ERR (struct cache_detail*) ; 
 struct cache_detail* cache_create_net (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  cache_destroy_net (struct cache_detail*,struct net*) ; 
 int cache_register_net (struct cache_detail*,struct net*) ; 
 int /*<<< orphan*/  ip_map_cache_template ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

int ip_map_cache_create(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct cache_detail *cd;
	int err;

	cd = cache_create_net(&ip_map_cache_template, net);
	if (IS_ERR(cd))
		return PTR_ERR(cd);
	err = cache_register_net(cd, net);
	if (err) {
		cache_destroy_net(cd, net);
		return err;
	}
	sn->ip_map_cache = cd;
	return 0;
}