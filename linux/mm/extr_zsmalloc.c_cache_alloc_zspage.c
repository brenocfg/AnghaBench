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
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_HIGHMEM ; 
 int __GFP_MOVABLE ; 
 struct zspage* kmem_cache_alloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct zspage *cache_alloc_zspage(struct zs_pool *pool, gfp_t flags)
{
	return kmem_cache_alloc(pool->zspage_cachep,
			flags & ~(__GFP_HIGHMEM|__GFP_MOVABLE));
}