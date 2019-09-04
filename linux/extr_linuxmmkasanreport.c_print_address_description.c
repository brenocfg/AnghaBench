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
struct page {struct kmem_cache* slab_cache; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageSlab (struct page*) ; 
 struct page* addr_to_page (void*) ; 
 int /*<<< orphan*/  describe_object (struct kmem_cache*,void*,void*) ; 
 int /*<<< orphan*/  dump_page (struct page*,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  init_task_stack_addr (void*) ; 
 scalar_t__ kernel_or_module_addr (void*) ; 
 void* nearest_obj (struct kmem_cache*,struct page*,void*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void print_address_description(void *addr)
{
	struct page *page = addr_to_page(addr);

	dump_stack();
	pr_err("\n");

	if (page && PageSlab(page)) {
		struct kmem_cache *cache = page->slab_cache;
		void *object = nearest_obj(cache, page,	addr);

		describe_object(cache, object, addr);
	}

	if (kernel_or_module_addr(addr) && !init_task_stack_addr(addr)) {
		pr_err("The buggy address belongs to the variable:\n");
		pr_err(" %pS\n", addr);
	}

	if (page) {
		pr_err("The buggy address belongs to the page:\n");
		dump_page(page, "kasan: bad access detected");
	}
}