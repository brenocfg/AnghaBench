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
struct seq_file {int dummy; } ;
struct afs_net {int /*<<< orphan*/  ws_cell; } ;
struct afs_cell {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct afs_net* afs_seq2net_single (struct seq_file*) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct afs_cell* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_proc_rootcell_show(struct seq_file *m, void *v)
{
	struct afs_cell *cell;
	struct afs_net *net;

	net = afs_seq2net_single(m);
	if (rcu_access_pointer(net->ws_cell)) {
		rcu_read_lock();
		cell = rcu_dereference(net->ws_cell);
		if (cell)
			seq_printf(m, "%s\n", cell->name);
		rcu_read_unlock();
	}
	return 0;
}