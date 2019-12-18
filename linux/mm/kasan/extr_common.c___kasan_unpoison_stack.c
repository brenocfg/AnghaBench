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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kasan_unpoison_shadow (void*,size_t) ; 
 void* task_stack_page (struct task_struct*) ; 

__attribute__((used)) static void __kasan_unpoison_stack(struct task_struct *task, const void *sp)
{
	void *base = task_stack_page(task);
	size_t size = sp - base;

	kasan_unpoison_shadow(base, size);
}