#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mode; } ;
struct task_struct {TYPE_2__ seccomp; } ;
struct TYPE_8__ {TYPE_2__ seccomp; TYPE_1__* sighand; } ;
struct TYPE_6__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 scalar_t__ SECCOMP_MODE_DISABLED ; 
 int /*<<< orphan*/  TIF_SECCOMP ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_seccomp_filter (TYPE_3__*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_no_new_privs (TYPE_3__*) ; 
 int /*<<< orphan*/  task_set_no_new_privs (struct task_struct*) ; 

__attribute__((used)) static void copy_seccomp(struct task_struct *p)
{
#ifdef CONFIG_SECCOMP
	/*
	 * Must be called with sighand->lock held, which is common to
	 * all threads in the group. Holding cred_guard_mutex is not
	 * needed because this new task is not yet running and cannot
	 * be racing exec.
	 */
	assert_spin_locked(&current->sighand->siglock);

	/* Ref-count the new filter user, and assign it. */
	get_seccomp_filter(current);
	p->seccomp = current->seccomp;

	/*
	 * Explicitly enable no_new_privs here in case it got set
	 * between the task_struct being duplicated and holding the
	 * sighand lock. The seccomp state and nnp must be in sync.
	 */
	if (task_no_new_privs(current))
		task_set_no_new_privs(p);

	/*
	 * If the parent gained a seccomp mode after copying thread
	 * flags and between before we held the sighand lock, we have
	 * to manually enable the seccomp thread flag here.
	 */
	if (p->seccomp.mode != SECCOMP_MODE_DISABLED)
		set_tsk_thread_flag(p, TIF_SECCOMP);
#endif
}