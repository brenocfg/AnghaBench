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
struct rlimit {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 int aa_task_setrlimit (struct aa_label*,struct task_struct*,unsigned int,struct rlimit*) ; 
 int /*<<< orphan*/  unconfined (struct aa_label*) ; 

__attribute__((used)) static int apparmor_task_setrlimit(struct task_struct *task,
		unsigned int resource, struct rlimit *new_rlim)
{
	struct aa_label *label = __begin_current_label_crit_section();
	int error = 0;

	if (!unconfined(label))
		error = aa_task_setrlimit(label, task, resource, new_rlim);
	__end_current_label_crit_section(label);

	return error;
}