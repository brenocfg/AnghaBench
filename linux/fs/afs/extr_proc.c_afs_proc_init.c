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
struct seq_net_private {int dummy; } ;
struct proc_dir_entry {int dummy; } ;
struct afs_net {struct proc_dir_entry* proc_afs; TYPE_1__* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_proc_cells_ops ; 
 int /*<<< orphan*/  afs_proc_cells_write ; 
 int /*<<< orphan*/  afs_proc_rootcell_show ; 
 int /*<<< orphan*/  afs_proc_rootcell_write ; 
 int /*<<< orphan*/  afs_proc_servers_ops ; 
 int /*<<< orphan*/  afs_proc_stats_show ; 
 int /*<<< orphan*/  afs_proc_sysname_ops ; 
 int /*<<< orphan*/  afs_proc_sysname_write ; 
 int /*<<< orphan*/  proc_create_net (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_create_net_data_write (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_create_net_single (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_create_net_single_write (char*,int,struct proc_dir_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct proc_dir_entry* proc_net_mkdir (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_remove (struct proc_dir_entry*) ; 

int afs_proc_init(struct afs_net *net)
{
	struct proc_dir_entry *p;

	_enter("");

	p = proc_net_mkdir(net->net, "afs", net->net->proc_net);
	if (!p)
		goto error_dir;

	if (!proc_create_net_data_write("cells", 0644, p,
					&afs_proc_cells_ops,
					afs_proc_cells_write,
					sizeof(struct seq_net_private),
					NULL) ||
	    !proc_create_net_single_write("rootcell", 0644, p,
					  afs_proc_rootcell_show,
					  afs_proc_rootcell_write,
					  NULL) ||
	    !proc_create_net("servers", 0444, p, &afs_proc_servers_ops,
			     sizeof(struct seq_net_private)) ||
	    !proc_create_net_single("stats", 0444, p, afs_proc_stats_show, NULL) ||
	    !proc_create_net_data_write("sysname", 0644, p,
					&afs_proc_sysname_ops,
					afs_proc_sysname_write,
					sizeof(struct seq_net_private),
					NULL))
		goto error_tree;

	net->proc_afs = p;
	_leave(" = 0");
	return 0;

error_tree:
	proc_remove(p);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}