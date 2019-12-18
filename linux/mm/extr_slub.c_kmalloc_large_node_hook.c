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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* kasan_kmalloc_large (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_alloc (void*,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *kmalloc_large_node_hook(void *ptr, size_t size, gfp_t flags)
{
	ptr = kasan_kmalloc_large(ptr, size, flags);
	/* As ptr might get tagged, call kmemleak hook after KASAN. */
	kmemleak_alloc(ptr, size, 1, flags);
	return ptr;
}