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
struct zspage {int dummy; } ;
struct zs_pool {int /*<<< orphan*/  zspage_cachep; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct zspage*) ; 

__attribute__((used)) static void cache_free_zspage(struct zs_pool *pool, struct zspage *zspage)
{
	kmem_cache_free(pool->zspage_cachep, zspage);
}