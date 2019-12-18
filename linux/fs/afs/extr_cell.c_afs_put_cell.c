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
typedef  scalar_t__ time64_t ;
struct afs_net {int dummy; } ;
struct afs_cell {int /*<<< orphan*/  usage; TYPE_1__* vl_servers; scalar_t__ last_inactive; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {scalar_t__ nr_servers; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_cell_gc_delay ; 
 int /*<<< orphan*/  afs_set_cell_timer (struct afs_net*,scalar_t__) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_real_seconds () ; 

void afs_put_cell(struct afs_net *net, struct afs_cell *cell)
{
	time64_t now, expire_delay;

	if (!cell)
		return;

	_enter("%s", cell->name);

	now = ktime_get_real_seconds();
	cell->last_inactive = now;
	expire_delay = 0;
	if (cell->vl_servers->nr_servers)
		expire_delay = afs_cell_gc_delay;

	if (atomic_dec_return(&cell->usage) > 1)
		return;

	/* 'cell' may now be garbage collected. */
	afs_set_cell_timer(net, expire_delay);
}