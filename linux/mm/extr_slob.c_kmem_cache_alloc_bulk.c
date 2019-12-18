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
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int __kmem_cache_alloc_bulk (struct kmem_cache*,int /*<<< orphan*/ ,size_t,void**) ; 

int kmem_cache_alloc_bulk(struct kmem_cache *s, gfp_t flags, size_t size,
								void **p)
{
	return __kmem_cache_alloc_bulk(s, flags, size, p);
}