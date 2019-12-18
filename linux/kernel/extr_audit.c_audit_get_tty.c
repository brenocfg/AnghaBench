#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_6__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tty_struct* tty_kref_get (int /*<<< orphan*/ ) ; 

struct tty_struct *audit_get_tty(void)
{
	struct tty_struct *tty = NULL;
	unsigned long flags;

	spin_lock_irqsave(&current->sighand->siglock, flags);
	if (current->signal)
		tty = tty_kref_get(current->signal->tty);
	spin_unlock_irqrestore(&current->sighand->siglock, flags);
	return tty;
}