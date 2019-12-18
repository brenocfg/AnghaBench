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
struct kvm_vm_worker_thread_context {uintptr_t data; int err; int /*<<< orphan*/  init_done; int /*<<< orphan*/  thread_fn; int /*<<< orphan*/  parent; struct kvm* kvm; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  kvm_vm_thread_fn_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct kvm_vm_worker_thread_context*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vm_worker_thread ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int kvm_vm_create_worker_thread(struct kvm *kvm, kvm_vm_thread_fn_t thread_fn,
				uintptr_t data, const char *name,
				struct task_struct **thread_ptr)
{
	struct kvm_vm_worker_thread_context init_context = {};
	struct task_struct *thread;

	*thread_ptr = NULL;
	init_context.kvm = kvm;
	init_context.parent = current;
	init_context.thread_fn = thread_fn;
	init_context.data = data;
	init_completion(&init_context.init_done);

	thread = kthread_run(kvm_vm_worker_thread, &init_context,
			     "%s-%d", name, task_pid_nr(current));
	if (IS_ERR(thread))
		return PTR_ERR(thread);

	/* kthread_run is never supposed to return NULL */
	WARN_ON(thread == NULL);

	wait_for_completion(&init_context.init_done);

	if (!init_context.err)
		*thread_ptr = thread;

	return init_context.err;
}