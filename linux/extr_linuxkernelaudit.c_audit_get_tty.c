#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tty_struct* tty_kref_get (int /*<<< orphan*/ ) ; 

struct tty_struct *audit_get_tty(struct task_struct *tsk)
{
	struct tty_struct *tty = NULL;
	unsigned long flags;

	spin_lock_irqsave(&tsk->sighand->siglock, flags);
	if (tsk->signal)
		tty = tty_kref_get(tsk->signal->tty);
	spin_unlock_irqrestore(&tsk->sighand->siglock, flags);
	return tty;
}