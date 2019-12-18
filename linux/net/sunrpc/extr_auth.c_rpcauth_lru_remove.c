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
struct rpc_cred {int /*<<< orphan*/  cr_lru; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_credcache_lock ; 
 int /*<<< orphan*/  rpcauth_lru_remove_locked (struct rpc_cred*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rpcauth_lru_remove(struct rpc_cred *cred)
{
	if (list_empty(&cred->cr_lru))
		return;
	spin_lock(&rpc_credcache_lock);
	rpcauth_lru_remove_locked(cred);
	spin_unlock(&rpc_credcache_lock);
}