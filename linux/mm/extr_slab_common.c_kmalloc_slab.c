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
 size_t KMALLOC_MAX_CACHE_SIZE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct kmem_cache* ZERO_SIZE_PTR ; 
 unsigned int fls (size_t) ; 
 struct kmem_cache*** kmalloc_caches ; 
 size_t kmalloc_type (int /*<<< orphan*/ ) ; 
 unsigned int* size_index ; 
 size_t size_index_elem (size_t) ; 

struct kmem_cache *kmalloc_slab(size_t size, gfp_t flags)
{
	unsigned int index;

	if (size <= 192) {
		if (!size)
			return ZERO_SIZE_PTR;

		index = size_index[size_index_elem(size)];
	} else {
		if (WARN_ON_ONCE(size > KMALLOC_MAX_CACHE_SIZE))
			return NULL;
		index = fls(size - 1);
	}

	return kmalloc_caches[kmalloc_type(flags)][index];
}