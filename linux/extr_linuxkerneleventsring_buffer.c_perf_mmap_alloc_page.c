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
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int cpu_to_node (int) ; 
 void* page_address (struct page*) ; 

__attribute__((used)) static void *perf_mmap_alloc_page(int cpu)
{
	struct page *page;
	int node;

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	page = alloc_pages_node(node, GFP_KERNEL | __GFP_ZERO, 0);
	if (!page)
		return NULL;

	return page_address(page);
}