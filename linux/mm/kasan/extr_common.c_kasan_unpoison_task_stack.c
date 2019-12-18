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
 scalar_t__ THREAD_SIZE ; 
 int /*<<< orphan*/  __kasan_unpoison_stack (struct task_struct*,scalar_t__) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

void kasan_unpoison_task_stack(struct task_struct *task)
{
	__kasan_unpoison_stack(task, task_stack_page(task) + THREAD_SIZE);
}