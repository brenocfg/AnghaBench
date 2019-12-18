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
 int /*<<< orphan*/  AA_PTRACE_TRACE ; 
 struct aa_label* __begin_current_label_crit_section () ; 
 int /*<<< orphan*/  __end_current_label_crit_section (struct aa_label*) ; 
 struct aa_label* aa_get_task_label (struct task_struct*) ; 
 int aa_may_ptrace (struct aa_label*,struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 

__attribute__((used)) static int apparmor_ptrace_traceme(struct task_struct *parent)
{
	struct aa_label *tracer, *tracee;
	int error;

	tracee = __begin_current_label_crit_section();
	tracer = aa_get_task_label(parent);
	error = aa_may_ptrace(tracer, tracee, AA_PTRACE_TRACE);
	aa_put_label(tracer);
	__end_current_label_crit_section(tracee);

	return error;
}