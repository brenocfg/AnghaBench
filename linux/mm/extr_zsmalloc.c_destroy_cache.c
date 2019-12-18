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
struct zs_pool {int /*<<< orphan*/  zspage_cachep; int /*<<< orphan*/  handle_cachep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_cache(struct zs_pool *pool)
{
	kmem_cache_destroy(pool->handle_cachep);
	kmem_cache_destroy(pool->zspage_cachep);
}