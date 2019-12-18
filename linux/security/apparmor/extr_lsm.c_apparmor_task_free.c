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
 int /*<<< orphan*/  aa_free_task_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_ctx (struct task_struct*) ; 

__attribute__((used)) static void apparmor_task_free(struct task_struct *task)
{

	aa_free_task_ctx(task_ctx(task));
}