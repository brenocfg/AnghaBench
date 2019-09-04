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
struct TYPE_6__ {int /*<<< orphan*/  signal; } ;
struct TYPE_10__ {int /*<<< orphan*/  blocked; TYPE_4__* sighand; TYPE_3__* signal; TYPE_1__ pending; } ;
struct TYPE_9__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_7__ {int /*<<< orphan*/  signal; } ;
struct TYPE_8__ {TYPE_2__ shared_pending; } ;

/* Variables and functions */
 TYPE_5__* current ; 
 int /*<<< orphan*/  sigandsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigorsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_sigpending(sigset_t *set)
{
	spin_lock_irq(&current->sighand->siglock);
	sigorsets(set, &current->pending.signal,
		  &current->signal->shared_pending.signal);
	spin_unlock_irq(&current->sighand->siglock);

	/* Outside the lock because only this thread touches it.  */
	sigandsets(set, &current->blocked, set);
}