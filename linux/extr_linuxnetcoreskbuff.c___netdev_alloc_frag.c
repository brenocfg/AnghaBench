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
struct page_frag_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  netdev_alloc_cache ; 
 void* page_frag_alloc (struct page_frag_cache*,unsigned int,int /*<<< orphan*/ ) ; 
 struct page_frag_cache* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *__netdev_alloc_frag(unsigned int fragsz, gfp_t gfp_mask)
{
	struct page_frag_cache *nc;
	unsigned long flags;
	void *data;

	local_irq_save(flags);
	nc = this_cpu_ptr(&netdev_alloc_cache);
	data = page_frag_alloc(nc, fragsz, gfp_mask);
	local_irq_restore(flags);
	return data;
}