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
struct kmem_cache {int /*<<< orphan*/  object_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  _RET_IP_ ; 
 void* __do_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kmem_cache_free_bulk (struct kmem_cache*,size_t,void**) ; 
 int /*<<< orphan*/  cache_alloc_debugcheck_after_bulk (struct kmem_cache*,int /*<<< orphan*/ ,size_t,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_alloc_debugcheck_before (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slab_post_alloc_hook (struct kmem_cache*,int /*<<< orphan*/ ,size_t,void**) ; 
 struct kmem_cache* slab_pre_alloc_hook (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int slab_want_init_on_alloc (int /*<<< orphan*/ ,struct kmem_cache*) ; 
 scalar_t__ unlikely (int) ; 

int kmem_cache_alloc_bulk(struct kmem_cache *s, gfp_t flags, size_t size,
			  void **p)
{
	size_t i;

	s = slab_pre_alloc_hook(s, flags);
	if (!s)
		return 0;

	cache_alloc_debugcheck_before(s, flags);

	local_irq_disable();
	for (i = 0; i < size; i++) {
		void *objp = __do_cache_alloc(s, flags);

		if (unlikely(!objp))
			goto error;
		p[i] = objp;
	}
	local_irq_enable();

	cache_alloc_debugcheck_after_bulk(s, flags, size, p, _RET_IP_);

	/* Clear memory outside IRQ disabled section */
	if (unlikely(slab_want_init_on_alloc(flags, s)))
		for (i = 0; i < size; i++)
			memset(p[i], 0, s->object_size);

	slab_post_alloc_hook(s, flags, size, p);
	/* FIXME: Trace call missing. Christoph would like a bulk variant */
	return size;
error:
	local_irq_enable();
	cache_alloc_debugcheck_after_bulk(s, flags, i, p, _RET_IP_);
	slab_post_alloc_hook(s, flags, i, p);
	__kmem_cache_free_bulk(s, i, p);
	return 0;
}