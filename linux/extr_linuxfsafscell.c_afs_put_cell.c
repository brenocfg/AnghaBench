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
typedef  scalar_t__ time64_t ;
struct afs_net {int dummy; } ;
struct afs_cell {int /*<<< orphan*/  usage; int /*<<< orphan*/  flags; scalar_t__ last_inactive; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CELL_FL_DNS_FAIL ; 
 int /*<<< orphan*/  AFS_CELL_FL_NOT_FOUND ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ afs_cell_gc_delay ; 
 int /*<<< orphan*/  afs_set_cell_timer (struct afs_net*,scalar_t__) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void afs_put_cell(struct afs_net *net, struct afs_cell *cell)
{
	time64_t now, expire_delay;

	if (!cell)
		return;

	_enter("%s", cell->name);

	now = ktime_get_real_seconds();
	cell->last_inactive = now;
	expire_delay = 0;
	if (!test_bit(AFS_CELL_FL_DNS_FAIL, &cell->flags) &&
	    !test_bit(AFS_CELL_FL_NOT_FOUND, &cell->flags))
		expire_delay = afs_cell_gc_delay;

	if (atomic_dec_return(&cell->usage) > 1)
		return;

	/* 'cell' may now be garbage collected. */
	afs_set_cell_timer(net, expire_delay);
}