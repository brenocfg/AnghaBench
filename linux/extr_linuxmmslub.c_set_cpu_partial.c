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

__attribute__((used)) static void set_cpu_partial(struct kmem_cache *s)
{
#ifdef CONFIG_SLUB_CPU_PARTIAL
	/*
	 * cpu_partial determined the maximum number of objects kept in the
	 * per cpu partial lists of a processor.
	 *
	 * Per cpu partial lists mainly contain slabs that just have one
	 * object freed. If they are used for allocation then they can be
	 * filled up again with minimal effort. The slab will never hit the
	 * per node partial lists and therefore no locking will be required.
	 *
	 * This setting also determines
	 *
	 * A) The number of objects from per cpu partial slabs dumped to the
	 *    per node list when we reach the limit.
	 * B) The number of objects in cpu partial slabs to extract from the
	 *    per node list when we run out of per cpu objects. We only fetch
	 *    50% to keep some capacity around for frees.
	 */
	if (!kmem_cache_has_cpu_partial(s))
		s->cpu_partial = 0;
	else if (s->size >= PAGE_SIZE)
		s->cpu_partial = 2;
	else if (s->size >= 1024)
		s->cpu_partial = 6;
	else if (s->size >= 256)
		s->cpu_partial = 13;
	else
		s->cpu_partial = 30;
#endif
}