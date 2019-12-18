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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int SKB_DATA_ALIGN (unsigned int) ; 
 void* __napi_alloc_frag (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ in_irq () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  netdev_alloc_cache ; 
 void* page_frag_alloc (struct page_frag_cache*,unsigned int,int /*<<< orphan*/ ) ; 
 struct page_frag_cache* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void *netdev_alloc_frag(unsigned int fragsz)
{
	struct page_frag_cache *nc;
	void *data;

	fragsz = SKB_DATA_ALIGN(fragsz);
	if (in_irq() || irqs_disabled()) {
		nc = this_cpu_ptr(&netdev_alloc_cache);
		data = page_frag_alloc(nc, fragsz, GFP_ATOMIC);
	} else {
		local_bh_disable();
		data = __napi_alloc_frag(fragsz, GFP_ATOMIC);
		local_bh_enable();
	}
	return data;
}