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
struct vmap_area {unsigned long va_start; unsigned long va_end; int /*<<< orphan*/ * vm; int /*<<< orphan*/  rb_node; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vmap_area* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int GFP_RECLAIM_MASK ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  SIZE_MAX ; 
 int __GFP_NOWARN ; 
 unsigned long __alloc_vmap_area (unsigned long,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ __this_cpu_cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vmap_area*) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ gfpflags_allow_blocking (int) ; 
 int /*<<< orphan*/  insert_vmap_area (struct vmap_area*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 struct vmap_area* kmem_cache_alloc_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vmap_area*) ; 
 int /*<<< orphan*/  kmemleak_scan_area (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  ne_fit_preload_node ; 
 int offset_in_page (unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  purge_vmap_area_lazy () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmap_area_cachep ; 
 int /*<<< orphan*/  vmap_area_list ; 
 int /*<<< orphan*/  vmap_area_lock ; 
 int /*<<< orphan*/  vmap_area_root ; 
 int /*<<< orphan*/  vmap_initialized ; 
 int /*<<< orphan*/  vmap_notify_list ; 

__attribute__((used)) static struct vmap_area *alloc_vmap_area(unsigned long size,
				unsigned long align,
				unsigned long vstart, unsigned long vend,
				int node, gfp_t gfp_mask)
{
	struct vmap_area *va, *pva;
	unsigned long addr;
	int purged = 0;

	BUG_ON(!size);
	BUG_ON(offset_in_page(size));
	BUG_ON(!is_power_of_2(align));

	if (unlikely(!vmap_initialized))
		return ERR_PTR(-EBUSY);

	might_sleep();

	va = kmem_cache_alloc_node(vmap_area_cachep,
			gfp_mask & GFP_RECLAIM_MASK, node);
	if (unlikely(!va))
		return ERR_PTR(-ENOMEM);

	/*
	 * Only scan the relevant parts containing pointers to other objects
	 * to avoid false negatives.
	 */
	kmemleak_scan_area(&va->rb_node, SIZE_MAX, gfp_mask & GFP_RECLAIM_MASK);

retry:
	/*
	 * Preload this CPU with one extra vmap_area object to ensure
	 * that we have it available when fit type of free area is
	 * NE_FIT_TYPE.
	 *
	 * The preload is done in non-atomic context, thus it allows us
	 * to use more permissive allocation masks to be more stable under
	 * low memory condition and high memory pressure.
	 *
	 * Even if it fails we do not really care about that. Just proceed
	 * as it is. "overflow" path will refill the cache we allocate from.
	 */
	preempt_disable();
	if (!__this_cpu_read(ne_fit_preload_node)) {
		preempt_enable();
		pva = kmem_cache_alloc_node(vmap_area_cachep, GFP_KERNEL, node);
		preempt_disable();

		if (__this_cpu_cmpxchg(ne_fit_preload_node, NULL, pva)) {
			if (pva)
				kmem_cache_free(vmap_area_cachep, pva);
		}
	}

	spin_lock(&vmap_area_lock);
	preempt_enable();

	/*
	 * If an allocation fails, the "vend" address is
	 * returned. Therefore trigger the overflow path.
	 */
	addr = __alloc_vmap_area(size, align, vstart, vend);
	if (unlikely(addr == vend))
		goto overflow;

	va->va_start = addr;
	va->va_end = addr + size;
	va->vm = NULL;
	insert_vmap_area(va, &vmap_area_root, &vmap_area_list);

	spin_unlock(&vmap_area_lock);

	BUG_ON(!IS_ALIGNED(va->va_start, align));
	BUG_ON(va->va_start < vstart);
	BUG_ON(va->va_end > vend);

	return va;

overflow:
	spin_unlock(&vmap_area_lock);
	if (!purged) {
		purge_vmap_area_lazy();
		purged = 1;
		goto retry;
	}

	if (gfpflags_allow_blocking(gfp_mask)) {
		unsigned long freed = 0;
		blocking_notifier_call_chain(&vmap_notify_list, 0, &freed);
		if (freed > 0) {
			purged = 0;
			goto retry;
		}
	}

	if (!(gfp_mask & __GFP_NOWARN) && printk_ratelimit())
		pr_warn("vmap allocation for size %lu failed: use vmalloc=<size> to increase size\n",
			size);

	kmem_cache_free(vmap_area_cachep, va);
	return ERR_PTR(-EBUSY);
}