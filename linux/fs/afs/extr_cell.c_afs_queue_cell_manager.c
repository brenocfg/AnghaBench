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
struct afs_net {int /*<<< orphan*/  cells_manager; int /*<<< orphan*/  cells_outstanding; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  afs_dec_cells_outstanding (struct afs_net*) ; 
 int /*<<< orphan*/  afs_wq ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void afs_queue_cell_manager(struct afs_net *net)
{
	int outstanding = atomic_inc_return(&net->cells_outstanding);

	_enter("%d", outstanding);

	if (!queue_work(afs_wq, &net->cells_manager))
		afs_dec_cells_outstanding(net);
}