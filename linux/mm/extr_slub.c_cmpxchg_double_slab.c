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
struct page {void* freelist; unsigned long counters; } ;
struct kmem_cache {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMPXCHG_DOUBLE_FAIL ; 
 int __CMPXCHG_DOUBLE ; 
 scalar_t__ cmpxchg_double (void**,unsigned long*,void*,unsigned long,void*,unsigned long) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slab_lock (struct page*) ; 
 int /*<<< orphan*/  slab_unlock (struct page*) ; 
 int /*<<< orphan*/  stat (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool cmpxchg_double_slab(struct kmem_cache *s, struct page *page,
		void *freelist_old, unsigned long counters_old,
		void *freelist_new, unsigned long counters_new,
		const char *n)
{
#if defined(CONFIG_HAVE_CMPXCHG_DOUBLE) && \
    defined(CONFIG_HAVE_ALIGNED_STRUCT_PAGE)
	if (s->flags & __CMPXCHG_DOUBLE) {
		if (cmpxchg_double(&page->freelist, &page->counters,
				   freelist_old, counters_old,
				   freelist_new, counters_new))
			return true;
	} else
#endif
	{
		unsigned long flags;

		local_irq_save(flags);
		slab_lock(page);
		if (page->freelist == freelist_old &&
					page->counters == counters_old) {
			page->freelist = freelist_new;
			page->counters = counters_new;
			slab_unlock(page);
			local_irq_restore(flags);
			return true;
		}
		slab_unlock(page);
		local_irq_restore(flags);
	}

	cpu_relax();
	stat(s, CMPXCHG_DOUBLE_FAIL);

#ifdef SLUB_DEBUG_CMPXCHG
	pr_info("%s %s: cmpxchg double redo ", n, s->name);
#endif

	return false;
}