#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ __sighandler_t ;
struct TYPE_10__ {TYPE_2__* sighand; int /*<<< orphan*/  pending; TYPE_1__* signal; } ;
struct TYPE_8__ {scalar_t__ sa_handler; } ;
struct TYPE_9__ {TYPE_3__ sa; } ;
struct TYPE_7__ {int /*<<< orphan*/  siglock; TYPE_4__* action; } ;
struct TYPE_6__ {int /*<<< orphan*/  shared_pending; } ;

/* Variables and functions */
 scalar_t__ SIG_IGN ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  flush_sigqueue_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recalc_sigpending () ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void kernel_sigaction(int sig, __sighandler_t action)
{
	spin_lock_irq(&current->sighand->siglock);
	current->sighand->action[sig - 1].sa.sa_handler = action;
	if (action == SIG_IGN) {
		sigset_t mask;

		sigemptyset(&mask);
		sigaddset(&mask, sig);

		flush_sigqueue_mask(&mask, &current->signal->shared_pending);
		flush_sigqueue_mask(&mask, &current->pending);
		recalc_sigpending();
	}
	spin_unlock_irq(&current->sighand->siglock);
}