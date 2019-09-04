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
struct TYPE_4__ {TYPE_1__* ring; int /*<<< orphan*/  ref; int /*<<< orphan*/  irq; } ;
struct sock_mapping {TYPE_2__ active; int /*<<< orphan*/  list; } ;
struct pvcalls_bedata {int /*<<< orphan*/  socket_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ref; } ;

/* Variables and functions */
 int PVCALLS_RING_ORDER ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sock_mapping*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int /*<<< orphan*/ ,struct sock_mapping*) ; 

__attribute__((used)) static void pvcalls_front_free_map(struct pvcalls_bedata *bedata,
				   struct sock_mapping *map)
{
	int i;

	unbind_from_irqhandler(map->active.irq, map);

	spin_lock(&bedata->socket_lock);
	if (!list_empty(&map->list))
		list_del_init(&map->list);
	spin_unlock(&bedata->socket_lock);

	for (i = 0; i < (1 << PVCALLS_RING_ORDER); i++)
		gnttab_end_foreign_access(map->active.ring->ref[i], 0, 0);
	gnttab_end_foreign_access(map->active.ref, 0, 0);
	free_page((unsigned long)map->active.ring);

	kfree(map);
}