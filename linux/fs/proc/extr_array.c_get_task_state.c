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
 scalar_t__ ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  TASK_REPORT_MAX ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 char const** task_state_array ; 
 size_t task_state_index (struct task_struct*) ; 

__attribute__((used)) static inline const char *get_task_state(struct task_struct *tsk)
{
	BUILD_BUG_ON(1 + ilog2(TASK_REPORT_MAX) != ARRAY_SIZE(task_state_array));
	return task_state_array[task_state_index(tsk)];
}