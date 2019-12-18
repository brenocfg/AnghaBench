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
struct kmem_cache {int flags; int remote_node_defrag_ratio; int /*<<< orphan*/  size; scalar_t__ offset; int /*<<< orphan*/  object_size; int /*<<< orphan*/  random; int /*<<< orphan*/  ctor; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  slab_flags_t ;

/* Variables and functions */
 int DEBUG_METADATA_FLAGS ; 
 int EINVAL ; 
 int SLAB_NO_CMPXCHG ; 
 scalar_t__ UP ; 
 int __CMPXCHG_DOUBLE ; 
 scalar_t__ alloc_kmem_cache_cpus (struct kmem_cache*) ; 
 int /*<<< orphan*/  calculate_sizes (struct kmem_cache*,int) ; 
 scalar_t__ disable_higher_order_debug ; 
 int /*<<< orphan*/  free_kmem_cache_nodes (struct kmem_cache*) ; 
 scalar_t__ get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_long () ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 scalar_t__ init_cache_random_seq (struct kmem_cache*) ; 
 int /*<<< orphan*/  init_kmem_cache_nodes (struct kmem_cache*) ; 
 int kmem_cache_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_partial (struct kmem_cache*) ; 
 int /*<<< orphan*/  set_min_partial (struct kmem_cache*,int) ; 
 scalar_t__ slab_state ; 
 scalar_t__ system_has_cmpxchg_double () ; 

__attribute__((used)) static int kmem_cache_open(struct kmem_cache *s, slab_flags_t flags)
{
	s->flags = kmem_cache_flags(s->size, flags, s->name, s->ctor);
#ifdef CONFIG_SLAB_FREELIST_HARDENED
	s->random = get_random_long();
#endif

	if (!calculate_sizes(s, -1))
		goto error;
	if (disable_higher_order_debug) {
		/*
		 * Disable debugging flags that store metadata if the min slab
		 * order increased.
		 */
		if (get_order(s->size) > get_order(s->object_size)) {
			s->flags &= ~DEBUG_METADATA_FLAGS;
			s->offset = 0;
			if (!calculate_sizes(s, -1))
				goto error;
		}
	}

#if defined(CONFIG_HAVE_CMPXCHG_DOUBLE) && \
    defined(CONFIG_HAVE_ALIGNED_STRUCT_PAGE)
	if (system_has_cmpxchg_double() && (s->flags & SLAB_NO_CMPXCHG) == 0)
		/* Enable fast mode */
		s->flags |= __CMPXCHG_DOUBLE;
#endif

	/*
	 * The larger the object size is, the more pages we want on the partial
	 * list to avoid pounding the page allocator excessively.
	 */
	set_min_partial(s, ilog2(s->size) / 2);

	set_cpu_partial(s);

#ifdef CONFIG_NUMA
	s->remote_node_defrag_ratio = 1000;
#endif

	/* Initialize the pre-computed randomized freelist if slab is up */
	if (slab_state >= UP) {
		if (init_cache_random_seq(s))
			goto error;
	}

	if (!init_kmem_cache_nodes(s))
		goto error;

	if (alloc_kmem_cache_cpus(s))
		return 0;

	free_kmem_cache_nodes(s);
error:
	return -EINVAL;
}