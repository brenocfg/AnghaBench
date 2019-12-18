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
struct vm_struct {int /*<<< orphan*/ * pages; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEMCG_KERNEL_STACK_KB ; 
 int PAGE_SIZE ; 
 int THREAD_SIZE ; 
 int memcg_kmem_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_memcg_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vm_struct* task_stack_vm_area (struct task_struct*) ; 

__attribute__((used)) static int memcg_charge_kernel_stack(struct task_struct *tsk)
{
#ifdef CONFIG_VMAP_STACK
	struct vm_struct *vm = task_stack_vm_area(tsk);
	int ret;

	if (vm) {
		int i;

		for (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++) {
			/*
			 * If memcg_kmem_charge() fails, page->mem_cgroup
			 * pointer is NULL, and both memcg_kmem_uncharge()
			 * and mod_memcg_page_state() in free_thread_stack()
			 * will ignore this page. So it's safe.
			 */
			ret = memcg_kmem_charge(vm->pages[i], GFP_KERNEL, 0);
			if (ret)
				return ret;

			mod_memcg_page_state(vm->pages[i],
					     MEMCG_KERNEL_STACK_KB,
					     PAGE_SIZE / 1024);
		}
	}
#endif
	return 0;
}