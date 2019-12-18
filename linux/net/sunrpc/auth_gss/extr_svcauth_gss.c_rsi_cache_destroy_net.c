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
struct sunrpc_net {struct cache_detail* rsi_cache; } ;
struct net {int dummy; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_destroy_net (struct cache_detail*,struct net*) ; 
 int /*<<< orphan*/  cache_purge (struct cache_detail*) ; 
 int /*<<< orphan*/  cache_unregister_net (struct cache_detail*,struct net*) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static void rsi_cache_destroy_net(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct cache_detail *cd = sn->rsi_cache;

	sn->rsi_cache = NULL;
	cache_purge(cd);
	cache_unregister_net(cd, net);
	cache_destroy_net(cd, net);
}