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

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  rpc_credcache_lock ; 
 int /*<<< orphan*/  rpcauth_destroy_credlist (int /*<<< orphan*/ *) ; 
 unsigned long rpcauth_prune_expired (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long
rpcauth_cache_do_shrink(int nr_to_scan)
{
	LIST_HEAD(free);
	unsigned long freed;

	spin_lock(&rpc_credcache_lock);
	freed = rpcauth_prune_expired(&free, nr_to_scan);
	spin_unlock(&rpc_credcache_lock);
	rpcauth_destroy_credlist(&free);

	return freed;
}