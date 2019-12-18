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
struct seq_net_private {int dummy; } ;
struct proc_dir_entry {int dummy; } ;
struct afs_vl_seq_net_private {int dummy; } ;
struct afs_net {int /*<<< orphan*/  proc_afs; int /*<<< orphan*/  net; } ;
struct afs_cell {int /*<<< orphan*/  name; struct afs_net* net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _enter (char*,struct afs_cell*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_proc_cell_vlservers_ops ; 
 int /*<<< orphan*/  afs_proc_cell_volumes_ops ; 
 int /*<<< orphan*/  proc_create_net_data (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ *,int,struct afs_cell*) ; 
 struct proc_dir_entry* proc_net_mkdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_subtree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int afs_proc_cell_setup(struct afs_cell *cell)
{
	struct proc_dir_entry *dir;
	struct afs_net *net = cell->net;

	_enter("%p{%s},%p", cell, cell->name, net->proc_afs);

	dir = proc_net_mkdir(net->net, cell->name, net->proc_afs);
	if (!dir)
		goto error_dir;

	if (!proc_create_net_data("vlservers", 0444, dir,
				  &afs_proc_cell_vlservers_ops,
				  sizeof(struct afs_vl_seq_net_private),
				  cell) ||
	    !proc_create_net_data("volumes", 0444, dir,
				  &afs_proc_cell_volumes_ops,
				  sizeof(struct seq_net_private),
				  cell))
		goto error_tree;

	_leave(" = 0");
	return 0;

error_tree:
	remove_proc_subtree(cell->name, net->proc_afs);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}