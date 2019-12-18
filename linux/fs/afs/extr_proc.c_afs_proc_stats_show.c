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
struct afs_net {int /*<<< orphan*/  n_store_bytes; int /*<<< orphan*/  n_stores; int /*<<< orphan*/  n_fetch_bytes; int /*<<< orphan*/  n_fetches; int /*<<< orphan*/  n_dir_rm; int /*<<< orphan*/  n_dir_cr; int /*<<< orphan*/  n_read_dir; int /*<<< orphan*/  n_relpg; int /*<<< orphan*/  n_inval; int /*<<< orphan*/  n_reval; int /*<<< orphan*/  n_lookup; } ;

/* Variables and functions */
 struct afs_net* afs_seq2net_single (struct seq_file*) ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int afs_proc_stats_show(struct seq_file *m, void *v)
{
	struct afs_net *net = afs_seq2net_single(m);

	seq_puts(m, "kAFS statistics\n");

	seq_printf(m, "dir-mgmt: look=%u reval=%u inval=%u relpg=%u\n",
		   atomic_read(&net->n_lookup),
		   atomic_read(&net->n_reval),
		   atomic_read(&net->n_inval),
		   atomic_read(&net->n_relpg));

	seq_printf(m, "dir-data: rdpg=%u\n",
		   atomic_read(&net->n_read_dir));

	seq_printf(m, "dir-edit: cr=%u rm=%u\n",
		   atomic_read(&net->n_dir_cr),
		   atomic_read(&net->n_dir_rm));

	seq_printf(m, "file-rd : n=%u nb=%lu\n",
		   atomic_read(&net->n_fetches),
		   atomic_long_read(&net->n_fetch_bytes));
	seq_printf(m, "file-wr : n=%u nb=%lu\n",
		   atomic_read(&net->n_stores),
		   atomic_long_read(&net->n_store_bytes));
	return 0;
}