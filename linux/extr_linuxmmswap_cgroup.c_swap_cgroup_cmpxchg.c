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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct swap_cgroup_ctrl {int /*<<< orphan*/  lock; } ;
struct swap_cgroup {unsigned short id; } ;

/* Variables and functions */
 struct swap_cgroup* lookup_swap_cgroup (int /*<<< orphan*/ ,struct swap_cgroup_ctrl**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned short swap_cgroup_cmpxchg(swp_entry_t ent,
					unsigned short old, unsigned short new)
{
	struct swap_cgroup_ctrl *ctrl;
	struct swap_cgroup *sc;
	unsigned long flags;
	unsigned short retval;

	sc = lookup_swap_cgroup(ent, &ctrl);

	spin_lock_irqsave(&ctrl->lock, flags);
	retval = sc->id;
	if (retval == old)
		sc->id = new;
	else
		retval = 0;
	spin_unlock_irqrestore(&ctrl->lock, flags);
	return retval;
}