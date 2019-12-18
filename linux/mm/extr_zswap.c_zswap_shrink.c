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
struct zswap_pool {int /*<<< orphan*/  zpool; } ;

/* Variables and functions */
 int ENOENT ; 
 int zpool_shrink (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct zswap_pool* zswap_pool_last_get () ; 
 int /*<<< orphan*/  zswap_pool_put (struct zswap_pool*) ; 

__attribute__((used)) static int zswap_shrink(void)
{
	struct zswap_pool *pool;
	int ret;

	pool = zswap_pool_last_get();
	if (!pool)
		return -ENOENT;

	ret = zpool_shrink(pool->zpool, 1, NULL);

	zswap_pool_put(pool);

	return ret;
}