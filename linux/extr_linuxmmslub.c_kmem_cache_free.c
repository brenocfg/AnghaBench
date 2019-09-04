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
 int /*<<< orphan*/  _RET_IP_ ; 
 struct kmem_cache* cache_from_obj (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  slab_free (struct kmem_cache*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 

void kmem_cache_free(struct kmem_cache *s, void *x)
{
	s = cache_from_obj(s, x);
	if (!s)
		return;
	slab_free(s, virt_to_head_page(x), x, NULL, 1, _RET_IP_);
	trace_kmem_cache_free(_RET_IP_, x);
}