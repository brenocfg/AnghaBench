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
struct task_struct {int /*<<< orphan*/  stack; int /*<<< orphan*/  stack_vm_area; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_KERNEL_STACK_KB ; 
 int NR_CACHED_STACKS ; 
 int PAGE_SIZE ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  THREAD_SIZE_ORDER ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cached_stacks ; 
 int /*<<< orphan*/  memcg_kmem_uncharge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_memcg_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vm_struct* task_stack_vm_area (struct task_struct*) ; 
 int /*<<< orphan*/ * this_cpu_cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void free_thread_stack(struct task_struct *tsk)
{
#ifdef CONFIG_VMAP_STACK
	struct vm_struct *vm = task_stack_vm_area(tsk);

	if (vm) {
		int i;

		for (i = 0; i < THREAD_SIZE / PAGE_SIZE; i++) {
			mod_memcg_page_state(vm->pages[i],
					     MEMCG_KERNEL_STACK_KB,
					     -(int)(PAGE_SIZE / 1024));

			memcg_kmem_uncharge(vm->pages[i], 0);
		}

		for (i = 0; i < NR_CACHED_STACKS; i++) {
			if (this_cpu_cmpxchg(cached_stacks[i],
					NULL, tsk->stack_vm_area) != NULL)
				continue;

			return;
		}

		vfree_atomic(tsk->stack);
		return;
	}
#endif

	__free_pages(virt_to_page(tsk->stack), THREAD_SIZE_ORDER);
}