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
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_PTRACE_READ ; 
 int /*<<< orphan*/  AA_PTRACE_TRACE ; 
 unsigned int PTRACE_MODE_READ ; 
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 struct aa_label* aa_get_task_label (struct task_struct*) ; 
 int aa_may_ptrace (struct aa_label*,struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 

__attribute__((used)) static int apparmor_ptrace_access_check(struct task_struct *child,
					unsigned int mode)
{
	struct aa_label *tracer, *tracee;
	int error;

	tracer = __begin_current_label_crit_section();
	tracee = aa_get_task_label(child);
	error = aa_may_ptrace(tracer, tracee,
			(mode & PTRACE_MODE_READ) ? AA_PTRACE_READ
						  : AA_PTRACE_TRACE);
	aa_put_label(tracee);
	__end_current_label_crit_section(tracer);

	return error;
}