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
struct mount {int /*<<< orphan*/  mnt_slave_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_MNT_NEW (struct mount*) ; 
 struct mount* last_slave (struct mount*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mount *skip_propagation_subtree(struct mount *m,
						struct mount *origin)
{
	/*
	 * Advance m such that propagation_next will not return
	 * the slaves of m.
	 */
	if (!IS_MNT_NEW(m) && !list_empty(&m->mnt_slave_list))
		m = last_slave(m);

	return m;
}