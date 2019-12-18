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
struct zs_pool {int /*<<< orphan*/  handle_cachep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void cache_free_handle(struct zs_pool *pool, unsigned long handle)
{
	kmem_cache_free(pool->handle_cachep, (void *)handle);
}