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

/* Variables and functions */

__attribute__((used)) static inline void *freelist_ptr(const struct kmem_cache *s, void *ptr,
				 unsigned long ptr_addr)
{
#ifdef CONFIG_SLAB_FREELIST_HARDENED
	return (void *)((unsigned long)ptr ^ s->random ^ ptr_addr);
#else
	return ptr;
#endif
}