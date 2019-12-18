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
 int /*<<< orphan*/  PTRACE_MODE_ATTACH ; 
 struct aa_label* aa_get_task_label (struct task_struct*) ; 
 int aa_may_ptrace (struct aa_label*,struct aa_label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_label (struct aa_label*) ; 
 int /*<<< orphan*/  current ; 
 struct task_struct* ptrace_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unconfined (struct aa_label*) ; 

__attribute__((used)) static int may_change_ptraced_domain(struct aa_label *to_label,
				     const char **info)
{
	struct task_struct *tracer;
	struct aa_label *tracerl = NULL;
	int error = 0;

	rcu_read_lock();
	tracer = ptrace_parent(current);
	if (tracer)
		/* released below */
		tracerl = aa_get_task_label(tracer);

	/* not ptraced */
	if (!tracer || unconfined(tracerl))
		goto out;

	error = aa_may_ptrace(tracerl, to_label, PTRACE_MODE_ATTACH);

out:
	rcu_read_unlock();
	aa_put_label(tracerl);

	if (error)
		*info = "ptrace prevents transition";
	return error;
}