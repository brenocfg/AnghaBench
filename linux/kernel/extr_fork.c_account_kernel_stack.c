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
struct vm_struct {int nr_pages; struct page** pages; } ;
struct task_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CONFIG_VMAP_STACK ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCG_KERNEL_STACK_KB ; 
 int /*<<< orphan*/  NR_KERNEL_STACK_KB ; 
 int PAGE_SIZE ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  mod_memcg_page_state (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 void* task_stack_page (struct task_struct*) ; 
 struct vm_struct* task_stack_vm_area (struct task_struct*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void account_kernel_stack(struct task_struct *tsk, int account)
{
	void *stack = task_stack_page(tsk);
	struct vm_struct *vm = task_stack_vm_area(tsk);

	BUILD_BUG_ON(IS_ENABLED(CONFIG_VMAP_STACK) && PAGE_SIZE % 1024 != 0);

	if (vm) {
		int i;

		BUG_ON(vm->nr_pages != THREAD_SIZE / PAGE_SIZE);

		for (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++) {
			mod_zone_page_state(page_zone(vm->pages[i]),
					    NR_KERNEL_STACK_KB,
					    PAGE_SIZE / 1024 * account);
		}
	} else {
		/*
		 * All stack pages are in the same zone and belong to the
		 * same memcg.
		 */
		struct page *first_page = virt_to_page(stack);

		mod_zone_page_state(page_zone(first_page), NR_KERNEL_STACK_KB,
				    THREAD_SIZE / 1024 * account);

		mod_memcg_page_state(first_page, MEMCG_KERNEL_STACK_KB,
				     account * (THREAD_SIZE / 1024));
	}
}