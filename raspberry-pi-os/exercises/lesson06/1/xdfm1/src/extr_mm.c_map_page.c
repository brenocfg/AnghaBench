#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct user_page {unsigned long member_0; unsigned long member_1; } ;
struct TYPE_2__ {unsigned long pgd; unsigned long* kernel_pages; size_t kernel_pages_count; int /*<<< orphan*/  user_pages_count; struct user_page* user_pages; } ;
struct task_struct {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PGD_SHIFT ; 
 int /*<<< orphan*/  PMD_SHIFT ; 
 int /*<<< orphan*/  PUD_SHIFT ; 
 scalar_t__ VA_START ; 
 unsigned long get_free_page () ; 
 unsigned long map_table (unsigned long*,int /*<<< orphan*/ ,unsigned long,int*) ; 
 int /*<<< orphan*/  map_table_entry (unsigned long*,unsigned long,unsigned long) ; 

void map_page(struct task_struct *task, unsigned long va, unsigned long page){
	unsigned long pgd;
	if (!task->mm.pgd) {
		task->mm.pgd = get_free_page();
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = task->mm.pgd;
	}
	pgd = task->mm.pgd;
	int new_table;
	unsigned long pud = map_table((unsigned long *)(pgd + VA_START), PGD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pud;
	}
	unsigned long pmd = map_table((unsigned long *)(pud + VA_START) , PUD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pmd;
	}
	unsigned long pte = map_table((unsigned long *)(pmd + VA_START), PMD_SHIFT, va, &new_table);
	if (new_table) {
		task->mm.kernel_pages[++task->mm.kernel_pages_count] = pte;
	}
	map_table_entry((unsigned long *)(pte + VA_START), va, page);
	struct user_page p = {page, va};
	task->mm.user_pages[task->mm.user_pages_count++] = p;
}