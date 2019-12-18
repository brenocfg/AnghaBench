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
struct bpf_map {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  map_idr ; 
 int /*<<< orphan*/  map_idr_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void bpf_map_free_id(struct bpf_map *map, bool do_idr_lock)
{
	unsigned long flags;

	/* Offloaded maps are removed from the IDR store when their device
	 * disappears - even if someone holds an fd to them they are unusable,
	 * the memory is gone, all ops will fail; they are simply waiting for
	 * refcnt to drop to be freed.
	 */
	if (!map->id)
		return;

	if (do_idr_lock)
		spin_lock_irqsave(&map_idr_lock, flags);
	else
		__acquire(&map_idr_lock);

	idr_remove(&map_idr, map->id);
	map->id = 0;

	if (do_idr_lock)
		spin_unlock_irqrestore(&map_idr_lock, flags);
	else
		__release(&map_idr_lock);
}