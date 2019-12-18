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
struct zswap_pool {int /*<<< orphan*/  zpool; int /*<<< orphan*/  tfm; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUHP_MM_ZSWP_POOL_PREPARE ; 
 int /*<<< orphan*/  cpuhp_state_remove_instance (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zswap_pool*) ; 
 int /*<<< orphan*/  zpool_destroy_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zswap_pool_debug (char*,struct zswap_pool*) ; 

__attribute__((used)) static void zswap_pool_destroy(struct zswap_pool *pool)
{
	zswap_pool_debug("destroying", pool);

	cpuhp_state_remove_instance(CPUHP_MM_ZSWP_POOL_PREPARE, &pool->node);
	free_percpu(pool->tfm);
	zpool_destroy_pool(pool->zpool);
	kfree(pool);
}