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
struct page {unsigned long counters; int /*<<< orphan*/  frozen; int /*<<< orphan*/  objects; int /*<<< orphan*/  inuse; void* freelist; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __cmpxchg_double_slab (struct kmem_cache*,struct page*,void*,unsigned long,int /*<<< orphan*/ *,unsigned long,char*) ; 

__attribute__((used)) static inline void *get_freelist(struct kmem_cache *s, struct page *page)
{
	struct page new;
	unsigned long counters;
	void *freelist;

	do {
		freelist = page->freelist;
		counters = page->counters;

		new.counters = counters;
		VM_BUG_ON(!new.frozen);

		new.inuse = page->objects;
		new.frozen = freelist != NULL;

	} while (!__cmpxchg_double_slab(s, page,
		freelist, counters,
		NULL, new.counters,
		"get_freelist"));

	return freelist;
}