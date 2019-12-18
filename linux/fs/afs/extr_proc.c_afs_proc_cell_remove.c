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
struct afs_net {int /*<<< orphan*/  proc_afs; } ;
struct afs_cell {int /*<<< orphan*/  name; struct afs_net* net; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  remove_proc_subtree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void afs_proc_cell_remove(struct afs_cell *cell)
{
	struct afs_net *net = cell->net;

	_enter("");
	remove_proc_subtree(cell->name, net->proc_afs);
	_leave("");
}