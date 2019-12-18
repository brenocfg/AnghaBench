#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct neighbour {int dead; TYPE_1__* tbl; int /*<<< orphan*/  gc_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  gc_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neigh_mark_dead(struct neighbour *n)
{
	n->dead = 1;
	if (!list_empty(&n->gc_list)) {
		list_del_init(&n->gc_list);
		atomic_dec(&n->tbl->gc_entries);
	}
}