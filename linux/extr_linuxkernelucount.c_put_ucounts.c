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
struct ucounts {int /*<<< orphan*/  node; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ucounts*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucounts_lock ; 

__attribute__((used)) static void put_ucounts(struct ucounts *ucounts)
{
	unsigned long flags;

	spin_lock_irqsave(&ucounts_lock, flags);
	ucounts->count -= 1;
	if (!ucounts->count)
		hlist_del_init(&ucounts->node);
	else
		ucounts = NULL;
	spin_unlock_irqrestore(&ucounts_lock, flags);

	kfree(ucounts);
}