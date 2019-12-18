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
struct task_struct {int flags; int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int PF_EXITING ; 
 int SIGKILL ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  signal_pending (struct task_struct*) ; 
 scalar_t__ task_curr (struct task_struct*) ; 
 scalar_t__ task_is_stopped_or_traced (struct task_struct*) ; 

__attribute__((used)) static inline bool wants_signal(int sig, struct task_struct *p)
{
	if (sigismember(&p->blocked, sig))
		return false;

	if (p->flags & PF_EXITING)
		return false;

	if (sig == SIGKILL)
		return true;

	if (task_is_stopped_or_traced(p))
		return false;

	return task_curr(p) || !signal_pending(p);
}