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
struct rpc_cred_cache {struct rpc_cred_cache* hashtable; } ;
struct rpc_auth {struct rpc_cred_cache* au_credcache; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpc_cred_cache*) ; 
 int /*<<< orphan*/  rpcauth_clear_credcache (struct rpc_cred_cache*) ; 

void
rpcauth_destroy_credcache(struct rpc_auth *auth)
{
	struct rpc_cred_cache *cache = auth->au_credcache;

	if (cache) {
		auth->au_credcache = NULL;
		rpcauth_clear_credcache(cache);
		kfree(cache->hashtable);
		kfree(cache);
	}
}