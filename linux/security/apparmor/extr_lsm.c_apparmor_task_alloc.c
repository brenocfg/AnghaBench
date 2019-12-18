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
struct aa_task_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_dup_task_ctx (struct aa_task_ctx*,struct aa_task_ctx*) ; 
 struct task_struct* current ; 
 struct aa_task_ctx* task_ctx (struct task_struct*) ; 

__attribute__((used)) static int apparmor_task_alloc(struct task_struct *task,
			       unsigned long clone_flags)
{
	struct aa_task_ctx *new = task_ctx(task);

	aa_dup_task_ctx(new, task_ctx(current));

	return 0;
}