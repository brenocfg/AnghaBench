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
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct mount {int /*<<< orphan*/  mnt_slave_list; TYPE_1__ mnt_slave; struct mount* mnt_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MNT_NEW (struct mount*) ; 
 struct mount* first_slave (struct mount*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct mount* next_peer (struct mount*) ; 
 struct mount* next_slave (struct mount*) ; 

__attribute__((used)) static struct mount *propagation_next(struct mount *m,
					 struct mount *origin)
{
	/* are there any slaves of this mount? */
	if (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
		return first_slave(m);

	while (1) {
		struct mount *master = m->mnt_master;

		if (master == origin->mnt_master) {
			struct mount *next = next_peer(m);
			return (next == origin) ? NULL : next;
		} else if (m->mnt_slave.next != &master->mnt_slave_list)
			return next_slave(m);

		/* back at master */
		m = master;
	}
}