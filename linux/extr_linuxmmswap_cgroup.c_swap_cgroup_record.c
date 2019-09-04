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
typedef  unsigned int pgoff_t ;

/* Variables and functions */
 unsigned int SC_PER_PAGE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 struct swap_cgroup* __lookup_swap_cgroup (struct swap_cgroup_ctrl*,unsigned int) ; 
 struct swap_cgroup* lookup_swap_cgroup (int /*<<< orphan*/ ,struct swap_cgroup_ctrl**) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int swp_offset (int /*<<< orphan*/ ) ; 

unsigned short swap_cgroup_record(swp_entry_t ent, unsigned short id,
				  unsigned int nr_ents)
{
	struct swap_cgroup_ctrl *ctrl;
	struct swap_cgroup *sc;
	unsigned short old;
	unsigned long flags;
	pgoff_t offset = swp_offset(ent);
	pgoff_t end = offset + nr_ents;

	sc = lookup_swap_cgroup(ent, &ctrl);

	spin_lock_irqsave(&ctrl->lock, flags);
	old = sc->id;
	for (;;) {
		VM_BUG_ON(sc->id != old);
		sc->id = id;
		offset++;
		if (offset == end)
			break;
		if (offset % SC_PER_PAGE)
			sc++;
		else
			sc = __lookup_swap_cgroup(ctrl, offset);
	}
	spin_unlock_irqrestore(&ctrl->lock, flags);

	return old;
}