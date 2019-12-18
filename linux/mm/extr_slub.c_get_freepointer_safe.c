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
struct kmem_cache {unsigned long offset; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int /*<<< orphan*/  debug_pagealloc_enabled () ; 
 void* freelist_ptr (struct kmem_cache*,void*,unsigned long) ; 
 void* get_freepointer (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  probe_kernel_read (void**,void**,int) ; 

__attribute__((used)) static inline void *get_freepointer_safe(struct kmem_cache *s, void *object)
{
	unsigned long freepointer_addr;
	void *p;

	if (!debug_pagealloc_enabled())
		return get_freepointer(s, object);

	freepointer_addr = (unsigned long)object + s->offset;
	probe_kernel_read(&p, (void **)freepointer_addr, sizeof(p));
	return freelist_ptr(s, p, freepointer_addr);
}