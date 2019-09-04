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
struct ida {int /*<<< orphan*/  ida_rt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ida_remove (struct ida*,unsigned int) ; 
 int /*<<< orphan*/  xa_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xa_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ida_free(struct ida *ida, unsigned int id)
{
	unsigned long flags;

	BUG_ON((int)id < 0);
	xa_lock_irqsave(&ida->ida_rt, flags);
	ida_remove(ida, id);
	xa_unlock_irqrestore(&ida->ida_rt, flags);
}